#include <incl/domain/arduino.h>

QString ArduinoDevice::getIpAddress() {
    return ipAddress;
}

void ArduinoDevice::setIpAddress(QString value) {
    ipAddress = value;
}

qint16 ArduinoDevice::getPort() {
    return port;
}

void ArduinoDevice::setPort(qint16 port) {
    ArduinoDevice::port = port;
}

void ArduinoDevice::setName(QString name) {
    ArduinoDevice::name = name;
}

QString ArduinoDevice::getName()  {
    return name;
}

QString ArduinoDevice::getDescription()  {
    return description;
}

void ArduinoDevice::setDescription(QString description) {
    ArduinoDevice::description = description;
}