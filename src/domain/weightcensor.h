#ifndef WEIGHTCENSOR_H
#define WEIGHTCENSOR_H

#include "recipe.h"
#include "iodevice.h"
#include <QObject>

class WeightCensor : public IODevice
{
    Q_GADGET

public:
    enum WeightSensorState {
        UNKNOWN, READY, TARGET_MET, TARGET_OVERFLOW, TARGET_UNDERFLOW
    };
    Q_ENUM(WeightSensorState);

    WeightCensor(int id, IO_DEVICE_HIGH_LOW deviceState);
    WeightCensor(int id, Recipe recipe);
    Recipe getRecipe() const;
    void setRecipe(Recipe);
    void updateRecipeWithComponentData(int, int);
    bool isDeviceStateLOW() const override;

private:
    Recipe recipe;
};
#endif // WEIGHTCENSOR_H

