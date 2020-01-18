#ifndef IODEVICE_H
#define IODEVICE_H

#include <QObject>
#include <QtCore/QString>
#include <QtCore/QJsonObject>
#include "arduino.h"
#include "action.h"
#include "iodevicetype.h"
#include "recipe.h"

enum IODeviceState { HIGH = 0, LOW = 1 };

class IODevice : public QObject {

Q_OBJECT
public:

    explicit IODevice(int _id);

    int getId() const;

    QString getDescription() const;
    void setDescription(const QString &_description);

    Arduino getArduino() const;
    void setArduino(const Arduino &_arduino);

    Action getAction() const;
    void setAction(const Action &_action);

    IODeviceType getIoDeviceType() const;
    void setIoDeviceType(const IODeviceType &_ioDeviceType);

    IODeviceState getDeviceState() const;
    void setDeviceState(IODeviceState _deviceState);

    void readJsonObject(QJsonObject jsonObject);

private:
    int id = 0;
    IODeviceState deviceState;
    QString description;
    Arduino arduino;
    Action action;
    IODeviceType ioDeviceType;

signals:
    void deviceStateValueChanged(IODeviceState newState);

};

#endif // IODEVICE_H
