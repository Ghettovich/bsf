#ifndef BSF_IODEVICE_H
#define BSF_IODEVICE_H

#include <QObject>
#include <QtCore/QString>
#include <QtCore/QJsonObject>
#include <domain/arduino.h>
#include <domain/action.h>
#include <domain/iodevicetype.h>
#include <domain/recipe.h>

class IODevice {

    Q_GADGET

public:
    enum IO_DEVICE_HIGH_LOW { HIGH, LOW };
    Q_ENUM(IO_DEVICE_HIGH_LOW);

    IODevice();
    IODevice(int id);
    int getId() const;

    QString getDescription() const;
    void setDescription(const QString &_description);

    Arduino getArduino() const;
    void setArduino(Arduino _arduino);

    Action getAction() const;
    void setAction(Action _action);

    IODeviceType getIoDeviceType() const;
    void setIoDeviceType(IODeviceType _ioDeviceType);

    IO_DEVICE_HIGH_LOW getDeviceState() const;
    void setDeviceState(IO_DEVICE_HIGH_LOW _deviceState);

    void readJsonObject(QJsonObject jsonObject);

    IODeviceType::IO_DEVICE_TYPE identifyDeviceType();

private:
    int id = 0;
    IO_DEVICE_HIGH_LOW deviceState;
    QString description;
    Arduino arduino;
    Action action;
    IODeviceType ioDeviceType;

};

#endif // IODEVICE_H
