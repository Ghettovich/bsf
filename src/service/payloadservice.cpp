#include "incl/service/payloadservice.h"
#include <incl/domain/transformpayload.h>

PayloadService::PayloadService(QObject *parent) : QObject(parent), ioDevice(0) {
    // REPO
    ioDeviceRepository = new IODeviceRepository;

    // ASSIGN MANAGER FROM FACTORY
    networkAccessManager = &NetworkRequestManagerSingleton::getInstance();

    qInfo() << networkAccessManager->objectName();
    // HOST (UDP) INFO
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(6677, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(onIncomingDatagrams()));
}

void PayloadService::requestStatePayload(const QString &url) {
    QNetworkRequest request;

    if (url.isEmpty()) {
        request.setUrl(QUrl("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/"));
    } else {
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

void PayloadService::requestIODeviceState(const QString &url, IODevice *_ioDevice) {
    requestStatePayload(url);
    ioDevice = _ioDevice;
}

void PayloadService::processJsonPayload() {
    QList<IODeviceDTO *> ioDeviceDTOList = TransformPayload::transformJSONPayloadToDtoIODeviceList(reply->readAll());
    // got payload
    if(ioDevice == nullptr) {
        emit onSendIODeviceDtoList(ioDeviceDTOList);
    }
    else if(ioDevice != nullptr && ioDevice->getId() != 0) {
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
    else {
        qInfo() << "dunno what to do o.0";
    }

    qInfo() << "done processing";
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
        QNetworkDatagram data = udpSocket->receiveDatagram();
        //processNetworkDatagram(data);
    }
}
