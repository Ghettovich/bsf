#include "headers/domain/weightcensor.h"

IODevice::IODevice()
{
}

qint16 IODevice::getDeviceId() const
{
return deviceId;
}

void IODevice::setDeviceId(const qint16 &value)
{
deviceId = value;
}

QString IODevice::getDeviceName() const
{
return deviceName;
}

void IODevice::setDeviceName(const QString &value)
{
deviceName = value;
}

QString IODevice::getDeviceDescription() const
{
return deviceDescription;
}

void IODevice::setDeviceDescription(const QString &value)
{
deviceDescription = value;
}
