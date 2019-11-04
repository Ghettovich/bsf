#ifndef WEIGHTCENSOR_H
#define WEIGHTCENSOR_H

#include "iodevice.h"


class WeightCensor : public IODevice
{

public:
    WeightCensor(qint16 deviceId, QString deviceName, QString deviceDescription);

    quint16 getMAX_WEIGHT() const;
    quint16 getCurrentWeight() const;
    void setCurrentWeight(const quint16 &value);

private:
    quint16 currentWeight;
    const quint16 MAX_WEIGHT = 1000;
};
#endif // WEIGHTCENSOR_H

