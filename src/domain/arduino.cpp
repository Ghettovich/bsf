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
    ioDeviceList.append(ioDevice);
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

QVector<IODevice *> Arduino::getIoDeviceList() {
    return ioDeviceList;
}

bool Arduino::hasRelayIODevices() {
    for(auto dev : ioDeviceList) {
        if(dev->getIoDeviceType().getIODeviceType() == IODeviceType::RELAY) {
            return true;
        }
    }

    return false;
}

bool Arduino::hasWeightSensorIODevices() {
    for(auto dev : ioDeviceList) {
        if(dev->getIoDeviceType().getIODeviceType() == IODeviceType::WEIGHTSENSOR) {
            return true;
        }
    }

    return false;
}

bool Arduino::hasDetectionSensorIODevices() {
    for(auto dev : ioDeviceList) {
        if(dev->getIoDeviceType().getIODeviceType() == IODeviceType::DETECTIONSENSOR) {
            return true;
        }
    }

    return false;
}

