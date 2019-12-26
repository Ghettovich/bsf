#include <incl/domain/recipe.h>

int Recipe::getId() const {
    return id;
}

const QString &Recipe::getDescription() const {
    return description;
}

void Recipe::setDescription(const QString &_description) {
    Recipe::description = _description;
}

int Recipe::getPlastifier() const {
    return plastifier;
}

void Recipe::setPlastifier(int _plastifier) {
    Recipe::plastifier = _plastifier;
}

int Recipe::getWater() const {
    return water;
}

void Recipe::setWater(int _water) {
    Recipe::water = _water;
}

int Recipe::getSand() const {
    return sand;
}

void Recipe::setSand(int _sand) {
    Recipe::sand = _sand;
}

bool Recipe::isPlastifierTargetMet(int target) {
    return target == plastifier;
}
