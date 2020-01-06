#include <incl/domain/recipe.h>

Recipe::Recipe(int id) : id(id) {
}

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

bool Recipe::isPlastifierTargetMet() {
    return currentWeightPlastifier == plastifier;
}

void Recipe::incrementCurrentWeightPlastifier(int weight) {
    currentWeightPlastifier += weight;
}

void Recipe::incrementCurrentWeightWater(int weight) {
    currentWeightWater += weight;
}

void Recipe::incrementCurrentWeightSand(int weight) {
    currentWeightSand += weight;
}

int Recipe::getCurrentWeightPlastifier() const {
    return currentWeightPlastifier;
}

int Recipe::getCurrentWeightWater() const {
    return currentWeightWater;
}

int Recipe::getCurrentWeightSand() const {
    return currentWeightSand;
}
