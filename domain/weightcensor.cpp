#include "headers/domain/weightcensor.h"

WeightCensor::WeightCensor(qint16 deviceId, QString deviceName, QString deviceDescription)
    : IODevice(deviceId, deviceName, deviceDescription)
{

}

quint16 WeightCensor::getMAX_WEIGHT() const
{
    return MAX_WEIGHT;
}

void WeightCensor::setCurrentWeight(const quint16 &value)
{
    currentWeight = value;
}

quint16 WeightCensor::getCurrentWeight() const
{
    return currentWeight;
}

