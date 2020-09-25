#include "weightcensor.h"
#include <utility>

WeightSensor::WeightSensor(int id, IODevice::IO_DEVICE_HIGH_LOW deviceState) : IODevice(id, deviceState) {}

WeightSensor::WeightSensor(int id, Recipe _recipe, IODevice::IO_DEVICE_HIGH_LOW deviceState)
    : IODevice(id, deviceState) {
    recipe = std::move(_recipe);
}

Recipe WeightSensor::getRecipe() const {
    return recipe;
}
void WeightSensor::setRecipe(Recipe _recipe) {
    recipe = std::move(_recipe);
}
void WeightSensor::updateRecipeWithComponentData(int componentId, int weight) {
    recipe.updateWeightForComponent(componentId, weight);
}
bool WeightSensor::isDeviceStateLOW() const {
    return getDeviceState() == LOW;
}
