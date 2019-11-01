#ifndef IODEVICE_H
#define IODEVICE_H

#include <QString>

class IODevice
{

public:
    IODevice();
    IODevice(qint16 deviceId, QString deviceName, QString deviceDescription)
        : deviceId(deviceId), deviceName(deviceName), deviceDescription(deviceDescription) {}
    QString getDeviceDescription() const;
    void setDeviceDescription(const QString &value);
    qint16 getDeviceId() const;
    void setDeviceId(const qint16 &value);
    QString getDeviceName() const;
    void setDeviceName(const QString &value);

private:
    qint16 deviceId = 0;
    QString deviceName = nullptr;
    QString deviceDescription = nullptr;
};

#endif // IODEVICE_H


