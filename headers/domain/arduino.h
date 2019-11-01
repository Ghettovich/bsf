#ifndef ARDUINO_H
#define ARDUINO_H

#include "iodevice.h"


class ArduinoDevice : public IODevice
{

public:
    ArduinoDevice();
    ArduinoDevice(QString ipAddress);

    QString getIpAddress() const;
    void setIpAddress(const QString &value);

private:
    QString ipAddress = nullptr;
};
#endif // ARDUINO_H

QString ArduinoDevice::getIpAddress() const
{
    return ipAddress;
}

void ArduinoDevice::setIpAddress(const QString &value)
{
    ipAddress = value;
}
