#include "pavementstateobject.h"
#include <utility>

PavementStateObject::PavementStateObject() = default;

Recipe PavementStateObject::getRecipe() const {
    return recipe;
}

void PavementStateObject::setRecipe(Recipe _recipe) {
    recipe = std::move(_recipe);
}

bool PavementStateObject::isRecipeTargetMet() {
    return recipe.isRecipeTargetMet();
}
