#include "incl/domain/iodevice.h"

IODevice::IODevice(int _id) :
        deviceState(IODeviceState::HIGH) {
    id = _id;
    deviceState = IODeviceState ::HIGH;
}

int IODevice::getId() const {
    return id;
}

QString IODevice::getDescription() const {
    return description;
}

void IODevice::setDescription(const QString &_description) {
    description = _description;
}

Arduino IODevice::getArduino() const {
    return arduino;
}

void IODevice::setArduino(const Arduino &_arduino) {
    arduino = _arduino;
}

Action IODevice::getAction() const {
    return action;
}

void IODevice::setAction(const Action &_action) {
    action = _action;
}

IODeviceType IODevice::getIoDeviceType() const {
    return ioDeviceType;
}

void IODevice::setIoDeviceType(const IODeviceType &_ioDeviceType) {
    ioDeviceType = _ioDeviceType;
}

IODeviceState IODevice::getDeviceState() const {
    return deviceState;
}

void IODevice::setDeviceState(IODeviceState _deviceState) {
    deviceState = _deviceState;
}

void IODevice::readJsonObject(QJsonObject jsonObject) {
    if(jsonObject.contains("id") && jsonObject["id"].toInt() == id) {
        // LOW MEANS ON
        if(jsonObject.contains("low") && jsonObject["low"].toInt() == IODeviceState::LOW) {
            deviceState = IODeviceState::LOW;
        }
        // HIGH IS OFF
        else if(jsonObject.contains("low") && jsonObject["low"].toInt() == IODeviceState::HIGH) {
            deviceState = IODeviceState::HIGH;
        }
        // device state unknown
        else {
            printf("%s", "unkown device state");
        }
    }
    else {
        printf("%s", "id's do not match, check implementation");
    }
}

