#include "weightcensor.h"
#include <utility>

WeightCensor::WeightCensor(int id, Recipe recipe) : IODevice(id), recipe(std::move(recipe)) { }

WeightCensor::WeightCensor(int id, IODevice::IO_DEVICE_HIGH_LOW deviceState) : IODevice(id, deviceState) {}

Recipe WeightCensor::getRecipe() const {
    return recipe;
}
void WeightCensor::setRecipe(Recipe _recipe) {
    recipe = std::move(_recipe);
}
void WeightCensor::updateRecipeWithComponentData(int componentId, int weight) {
    recipe.updateWeightForComponent(componentId, weight);
}
bool WeightCensor::isDeviceStateLOW() const {
    return getDeviceState() == LOW;
}
