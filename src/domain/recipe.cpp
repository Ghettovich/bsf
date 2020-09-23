#include "recipe.h"
#include <QtCore/QJsonArray>

Recipe::Recipe(int id) : id(id) {
    initRecipe();
}

void Recipe::initRecipe() {
    plastifier = 0;
    water = 0;
    sand = 0;
    currentWeightPlastifier = 0;
    currentWeightWater = 0;
    currentWeightSand = 0;
}

int Recipe::getId() const {
    return id;
}

int Recipe::getPlastifierId() const {
    return plastifierId;
}

void Recipe::setPlastifierId(int _plastifierId) {
    plastifierId = _plastifierId;
}

int Recipe::getWaterId() const {
    return waterId;
}

void Recipe::setWaterId(int _waterId) {
    waterId = _waterId;
}

int Recipe::getSandId() const {
    return sandId;
}

void Recipe::setSandId(int _sandId) {
    sandId = _sandId;
}

const QString &Recipe::getDescription() const {
    return description;
}

void Recipe::setDescription(const QString &_description) {
    description = _description;
}

int Recipe::getPlastifier() const {
    return plastifier;
}

void Recipe::setPlastifier(int _plastifier) {
    plastifier = _plastifier;
}

int Recipe::getWater() const {
    return water;
}

void Recipe::setWater(int _water) {
    water = _water;
}

int Recipe::getSand() const {
    return sand;
}

void Recipe::setSand(int _sand) {
    sand = _sand;
}

bool Recipe::isPlastifierTargetMet() {
    return currentWeightPlastifier == plastifier;
}

bool Recipe::isWaterTargetMet() {
    return currentWeightWater == water;
}

bool Recipe::isSandTargetMet() {
    return currentWeightSand == sand;
}

// ToDo:: Add rest of targets
bool Recipe::isRecipeTargetMet() {

    //return (isPlastifierTargetMet() && isWaterTargetMet() && isSandTargetMet());

    if(isPlastifierTargetMet() && isWaterTargetMet() && isSandTargetMet()) {
        return true;
    } else {
        return false;
    }

}

void Recipe::updateCurrentWeightPlastifier(int weight) {
    currentWeightPlastifier = weight;
}

void Recipe::updateCurrentWeightWater(int weight) {
    currentWeightWater = weight;
}

void Recipe::updateCurrentWeightSand(int weight) {
    currentWeightSand = weight;
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

void Recipe::writeJson(QJsonObject &json) {
    printf("\nbegin write json");
    json["recipeId"] = id;
    json["plastifierId"] = plastifierId;
    QJsonArray dataAray;
    dataAray.append(plastifier);
    // ToDo: replace with actual value when needed or set null if disgarded in future
    dataAray.append(5000);
    json["data"] = dataAray;

    printf("\nend write json");
}

void Recipe::updateWeightForComponent(int componentId, int weight) {
    switch(componentId) {
        case 1:
            updateCurrentWeightPlastifier(weight);
            break;
        case 2:
            updateCurrentWeightWater(weight);
            break;
        default:
            break;
    }
}

void Recipe::initActualComponentMap() {
    QMapIterator<int, int> i(targetComponentMap);

    while(i.hasNext()) {
        i.next();
        actualComponentMap.insert(i.key(), i.value());
    }
}
