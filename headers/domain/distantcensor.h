#ifndef DISTANTCENSOR_H
#define DISTANTCENSOR_H

#include "iodevice.h"


class DistantCensor : public IODevice {
public:
    DistantCensor();

    DistantCensor(quint16 preferedDistance, quint16 maxDistance);

    quint16 getPreferedDistance() const;
    void setPreferedDistance(const quint16 &value);

    quint16 getMaxDistance() const;
    void setMaxDistance(const quint16 &value);

private:
    quint16 preferedDistance;
    quint16 maxDistance;

};

#endif // DISTANTCENSOR_H

quint16 DistantCensor::getPreferedDistance() const {
    return preferedDistance;
}

void DistantCensor::setPreferedDistance(const quint16 &value) {
    preferedDistance = value;
}

quint16 DistantCensor::getMaxDistance() const {
    return maxDistance;
}

void DistantCensor::setMaxDistance(const quint16 &value) {
    maxDistance = value;
}
