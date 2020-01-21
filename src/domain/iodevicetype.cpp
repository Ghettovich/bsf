#include "iodevicetype.h"
#include <QMetaEnum>
#include <utility>

IODeviceType::IODeviceType(int id) :
        id(id) {
    ioDeviceType = (IO_DEVICE_TYPE(id));
}

int IODeviceType::getId() const {
    return id;
}

QString IODeviceType::getType() const {
    return type;
}

void IODeviceType::setType(QString _type) {
    type = std::move(_type);
}

QString IODeviceType::getDescription() const {
    return description;
}

void IODeviceType::setDescription(QString _description) {
    description = std::move(_description);
}

IODeviceType::IO_DEVICE_TYPE IODeviceType::getIODeviceType() {
    return DETECTIONSENSOR;
}

void IODeviceType::setIODeviceType(IO_DEVICE_TYPE _type) {
    ioDeviceType = _type;
}
