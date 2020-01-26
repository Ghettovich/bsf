#ifndef BSF_IODEVICE_H
#define BSF_IODEVICE_H

#include <domain/arduino.h>
#include <domain/action.h>
#include <domain/iodevicetype.h>
#include <domain/recipe.h>
#include <QObject>
#include <QtCore/QString>
#include <QtCore/QJsonObject>


class IODevice {

Q_GADGET

public:
    enum IO_DEVICE_HIGH_LOW {
        HIGH, LOW
    };
    Q_ENUM(IO_DEVICE_HIGH_LOW);

    explicit IODevice(int id = 0);
    IODevice(int id, IO_DEVICE_HIGH_LOW _deviceState);
    int getId() const;
    QString getDescription() const;
    void setDescription(const QString &_description);
    Arduino getArduino() const;
    void setArduino(const Arduino &_arduino);
    Action getAction() const;
    void setAction(const Action &_action);
    IODeviceType getIoDeviceType() const;
    void setIoDeviceType(const IODeviceType &_ioDeviceType);
    IO_DEVICE_HIGH_LOW getDeviceState() const;
    void setDeviceState(IO_DEVICE_HIGH_LOW _deviceState);

    virtual bool isDeviceStateLOW() const = 0;

private:
    int id = 0;
    IO_DEVICE_HIGH_LOW deviceState;
    QString description;
    Arduino arduino;
    Action action;
    IODeviceType ioDeviceType;

};

#endif // IODEVICE_H
