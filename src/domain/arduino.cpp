#include "arduino.h"
#include <QMetaEnum>

Arduino::Arduino(int id) : id(id) {
    arduinoState = UNKOWN;
}

QString Arduino::getDesc() const {
    return desc;
}

void Arduino::setDesc(const QString &_desc) {
    desc = _desc;
}

QString Arduino::getIpAddress() const {
    return ipAddress;
}

void Arduino::setIpAddress(const QString &_ipAddress) {
    ipAddress = _ipAddress;
}

QString Arduino::getName() const {
    return name;
}

void Arduino::setName(const QString &_name) {
    name = _name;
}

qint16 Arduino::getPort() const {
    return port;
}

void Arduino::setPort(qint16 _port) {
    port = _port;
}

int Arduino::getId() const {
    return id;
}
void Arduino::addIODevice(IODevice *ioDevice) {
    ioDeviceList->append(ioDevice);
}
QString Arduino::getStatusMessage() const {
    return statusMessage;
}
void Arduino::setStatusMessage(const QString &_statusMessage) {
    statusMessage = _statusMessage;
}

Arduino::ARDUINO_STATE Arduino::getArduinoState() {
    return arduinoState;
}

void Arduino::setArduinoState(Arduino::ARDUINO_STATE state) {
    arduinoState = state;
}

QVector<IODevice *>* Arduino::getIoDeviceList() {
    return ioDeviceList;
}
void Arduino::setIoDeviceList(QVector<IODevice *> *_ioDeviceList) {
    ioDeviceList = _ioDeviceList;
}

