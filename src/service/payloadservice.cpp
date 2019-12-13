#include "incl/service/payloadservice.h"
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkDatagram>
#include <incl/domain/iodevicepayload.h>
#include <incl/dto/iodevicedto.h>

PayloadService::PayloadService(QObject *parent) : QObject(parent) {
    // ASSIGN MANAGER FROM FACTORY
    networkAccessManager = &NetworkRequestManagerSingleton::getInstance();

    // HOST (UDP) INFO
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(6677, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(onIncomingDatagrams()));
}

void PayloadService::requestFullStatePayload() {
    QNetworkRequest request;
    request.setUrl(QUrl("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/"));
    reply = networkAccessManager->get(request);

    // CLIENT (TCP) INFO
    connect(reply, &QIODevice::readyRead, this, &PayloadService::httpReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &PayloadService::httpError);
}

void PayloadService::httpReadyRead() {
    // got payload
    //qInfo() << "got reply from service: " << reply->readAll().constData();
    // transform payload to io device list
    //IODevicePayload payload;
    //QList<IODevice *> ioDeviceList = payload.transformPayloadToIODeviceList(reply->readAll());
    QList<IODeviceDTO *> ioDeviceDTOList;
    QByteArray byteArray(reply->readAll().trimmed());
//    qInfo() << "raw = " << byteArray;
//    qInfo() << "constData =" << byteArray.constData();
    qInfo() <<"data =" << byteArray.data();
    QString csvRows = "";

    int i = 0, j = 1;
    QString part = "";
    bool shouldConvert = false;
    auto * ioDeviceDto = new IODeviceDTO();

    for(QChar c: byteArray) {
        // either a space, comma or value
        qInfo() << QString::number(byteArray.size());
        qInfo() << QString::number(j);

        if(c.isSpace() || (j == byteArray.size())) {
            // hit EOL, add last part
            i = 0;
            // add last value and clear part
            ioDeviceDto->isLOW = part.toInt() == 1;
            part.clear();
            // add to list
            ioDeviceDTOList.append(ioDeviceDto);
            ioDeviceDto = new IODeviceDTO();
            qInfo() << "hit space";
        }
        else if (c == ',') {
            qInfo() << "hit splitter, set convert true";
            shouldConvert = true;
        }
        if (shouldConvert) {
            qInfo() << "converted = " << part;
            switch (i) {
                case 0 :
                    ioDeviceDto->id = part.toInt();
                    break;
                case 1 :
                    ioDeviceDto->actionId = part.toInt();;
                    break;
                case 2 :
                    ioDeviceDto->typeId = part.toInt();;
                    break;
                default:
                    break;
            }
            i++;
            part.clear();
            shouldConvert = false;
        }
        if (c.isDigit()) {
            part.append(c);
            qInfo() << "append to string";
        }
        j++;
    }

    for (IODeviceDTO *dto : ioDeviceDTOList) {
        qInfo() << "id = " << QString::number(dto->id) << "actionId = " << QString::number(dto->actionId) << "state = " << (dto->isLOW ? "LOW TRUE" : "LOW FALSE");
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