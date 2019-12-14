#include "incl/service/payloadservice.h"
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkDatagram>
#include <incl/domain/transformpayload.h>
#include <incl/dto/iodevicedto.h>

PayloadService::PayloadService(QObject *parent) : QObject(parent) {
    // REPO
    ioDeviceRepository = new IODeviceRepository;

    // ASSIGN MANAGER FROM FACTORY
    networkAccessManager = &NetworkRequestManagerSingleton::getInstance();

    // HOST (UDP) INFO
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(6677, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(onIncomingDatagrams()));
}

//QList<IODevice *> createIODeviceListCurrentState() {
//    QList<IODevice *> ioDeviceList =
//}

void PayloadService::requestFullStatePayload() {
    QNetworkRequest request;
    request.setUrl(QUrl("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/"));
    reply = networkAccessManager->get(request);

    // CLIENT (TCP) INFO
    connect(reply, &QIODevice::readyRead, this, &PayloadService::httpReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &PayloadService::httpError);
}

void PayloadService::requestFullStatePayload(int ioDeviceId, IODevice *_ioDevice) {
    QList<IODeviceDTO *> ioDeviceDTOList = TransformPayload::transformJSONPayloadToDtoIODeviceList(reply->readAll());
    QList<IODevice *> ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(1, ioDeviceDTOList);

    for(auto * ioDevice: ioDeviceList) {
        if(ioDevice->id == ioDeviceId) {
            _ioDevice = ioDevice;
        }
    }
}

void PayloadService::httpReadyRead() {
    // got payload
    QList<IODeviceDTO *> ioDeviceDTOList = TransformPayload::transformJSONPayloadToDtoIODeviceList(reply->readAll());
    QList<IODevice *> ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(1, ioDeviceDTOList);

    qInfo() << "size " << QString::number(ioDeviceList.size());

    for (IODevice *dto : ioDeviceList) {
        qInfo() << "id = " << QString::number(dto->id) << "actionId = " << QString::number(dto->action.id);
    }
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