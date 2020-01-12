#include "incl/service/payloadservice.h"
#include <incl/domain/transformpayload.h>
#include <incl/domain/statecode.h>

PayloadService::PayloadService() {
    // ASSIGN MANAGER FROM FACTORY
    networkAccessManager = &NetworkRequestManagerSingleton::getInstance();

    qInfo() << networkAccessManager->objectName();
    // HOST (UDP) INFO
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(6677, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(onIncomingDatagrams()));

    udpSocketWeightStation = new QUdpSocket(this);
    udpSocketWeightStation->bind(6678, QUdpSocket::ShareAddress);
    connect(udpSocketWeightStation, SIGNAL(readyRead()),
            this, SLOT(onIncomingDatagramsWeightStation()));
}

void PayloadService::setStateObject(PavementStateObject *_stateObject) {
    stateObject = _stateObject;
    QObject::connect(this, &PayloadService::onUpdateStateObject,
                     stateObject, &PavementStateObject::updateIODevicesWithDto);
}

void PayloadService::requestStatePayload(const QString &url) {
    QNetworkRequest request;

    if (url.isEmpty()) {
        qInfo() << "got EMPTY url, falling back to arduino 1 full state payload";
        request.setUrl(QUrl("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/"));
    } else {
        qInfo() << "got url";
        request.setUrl(QUrl(url));
    }

    reply = networkAccessManager->get(request);
    qInfo() << "sending request...";

    // CLIENT (TCP) INFO
    connect(reply, &QIODevice::readyRead, this, &PayloadService::httpReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &PayloadService::httpError);

    qInfo() << "connected readyread";
}

void PayloadService::requestStatePayload(Arduino _arduino, const QString &url) {
    arduino = &_arduino;
    requestStatePayload(url);
}

void PayloadService::requestIODeviceState(const QString &url, IODevice *_ioDevice) {
    ioDevice = _ioDevice;
    requestStatePayload(url);
}

void PayloadService::broadcastRecipe(Recipe recipe, Arduino _arduino) {
    QJsonObject json;
    recipe.writeJson(json);
    QJsonDocument doc (json);
    QByteArray ba = doc.toJson();
    arduino = &_arduino;

    udpSocketWeightStation->writeDatagram(ba,
            QHostAddress(arduino->ipAddress), 6678);
}

void PayloadService::processJsonPayload() {
    QList<IODeviceDTO *> ioDeviceDTOList = TransformPayload::transformJSONPayloadToDtoIODeviceList(reply->readAll());
    updateIODevicesWithDto(ioDeviceDTOList);
}

void PayloadService::updateIODevicesWithDto(const QList<IODeviceDTO *>& ioDeviceDTOList) {
    // got payload
    if(ioDevice != nullptr && ioDevice->getId() != 0) {
        for (IODeviceDTO *dto: ioDeviceDTOList) {
            if (dto->id == ioDevice->getId()) {
                qInfo() << "got match for IODevice! setting new state\n got id: " << QString::number(ioDevice->getId());
                qInfo() << "dto id = " << QString::number(dto->id);
                if(dto->low == 1) {
                    qInfo() << "low = true (relay is ON)";
                }
                else {
                    qInfo() << "low = false (relay is OFF)";
                }
                // TODO: get rid of dereference pointer
                emit onReceiveIODeviceState(dto->low == 1 ? IODeviceState::LOW : IODeviceState::HIGH);
            }
        }

        ioDevice = nullptr;
    }
    else if(!stateObject->getIoDeviceList().empty() ||
    !stateObject->getIoDeviceListWeightStation().empty() ) {
        emit onUpdateStateObject(ioDeviceDTOList);
    }
    else {
        qInfo() << "dunno what to do o.0";
    }

    qInfo() << "done processing";
}

void PayloadService::processDatagram(const QByteArray &data) {
    ArduinoDTO arduinoDto = TransformPayload::transformJSONPayloadToArduinoDto(data);
    QList<IODeviceDTO *> ioDeviceDTOList = TransformPayload::transformJSONPayloadToDtoIODeviceList(data);
    //updateIODevicesWithDto(ioDeviceDTOList);

    if(stateObject == nullptr) {
        qInfo() << "no state object to update";
    }
    else if(arduinoDto.arduinoId > 0 && arduinoDto.arduinoId == arduino->id) {
        emit onUpdateStateObject(ioDeviceDTOList);

        arduino = nullptr;
    }
    // received payload, state of arduino has changed. e.g. detection sensor flipped.
    else {
        qInfo() << "state reply =" << QString::number(arduinoDto.stateReply);
        qInfo() << "arduino id ="<< QString::number(arduinoDto.arduinoId);
        //
        emit onUpdateStateObject(ioDeviceDTOList);
    }

    //udpSocket->close();
}

void PayloadService::processDatagramWeightStation(const QByteArray &data) {
    qInfo() << "processing datagrams weight station";
    ArduinoDTO arduinoDto = TransformPayload::transformJSONPayloadToArduinoDto(data);

    qInfo() << "state reply =" << QString::number(arduinoDto.stateReply);
    qInfo() << "arduino id ="<< QString::number(arduinoDto.arduinoId);

    if(arduino != nullptr && arduinoDto.arduinoId == arduino->id) {
        // weight station parsed json succesfully
        if(arduinoDto.stateReply == 0) {
            emit onReceiveWeightStationReply(data);
        }
        else if(arduinoDto.stateReply == 1) {
            qInfo() << "error occured at arduino 2";
        }

        arduino = nullptr;
    }
    else {
        qInfo() << "received UDP packets from WEIGHT STATION";
    }

    //udpSocketWeightStation->close();
}

void PayloadService::httpReadyRead() {
    qInfo() << "Ready for reading, start processing.";
    processJsonPayload();
}

void PayloadService::httpError() {
    qInfo() << "got http error" << reply->error();
}

void PayloadService::onIncomingDatagrams() {
    QByteArray datagram;
    qInfo() << "got incoming udp packets...";

    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpSocket->receiveDatagram();
        //qInfo() << receiveDatagram.data();
        processDatagram(receiveDatagram.data());
    }
}

void PayloadService::onIncomingDatagramsWeightStation() {
    QByteArray datagram;
    qInfo() << "got incoming udp packets from weight station...";

    while (udpSocketWeightStation->hasPendingDatagrams()) {
        datagram.resize(int(udpSocketWeightStation->pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpSocketWeightStation->receiveDatagram();
        processDatagramWeightStation(receiveDatagram.data());
    }
}
