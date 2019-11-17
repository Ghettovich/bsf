#include <incl/domain/detectioncensor.h>

DistantCensor::DistantCensor() {
    preferedDistance = 0;
    maxDistance = 0;
}

DistantCensor::DistantCensor(quint16 preferedDistance, quint16 maxDistance) {
    this->preferedDistance = preferedDistance;
    this->maxDistance = maxDistance;
}

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
