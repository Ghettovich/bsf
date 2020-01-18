#include "weightcensor.h"

WeightCensor::WeightCensor(int deviceId)
        : IODevice(deviceId) {
}

const Recipe *WeightCensor::getRecipe() const {
    return recipe;
}

void WeightCensor::setRecipe(Recipe *_recipe) {
    WeightCensor::recipe = _recipe;
}
