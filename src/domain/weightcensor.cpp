#include "weightcensor.h"
#include <utility>

WeightCensor::WeightCensor(int deviceId)
        : IODevice(deviceId) {
}

Recipe WeightCensor::getRecipe() const {
    return recipe;
}

void WeightCensor::setRecipe(Recipe _recipe) {
    recipe = std::move(_recipe);
}

void WeightCensor::updateRecipeWithComponentData(int componentId, int weight) {
    recipe.updateWeightForComponent(componentId, weight);
}
