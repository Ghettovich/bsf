#include "recipe.h"
#include <QtCore/QString>
#include <QtCore/QJsonObject>

Recipe::Recipe(int id) : id(id) {
    connect(this, SIGNAL(updateComponentWithNewWeight(int, int)),
            this, SLOT(onUpdateWithComponentWeightData(int, int)));
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

void Recipe::writeJson(QJsonObject &json) {
    json["recipeId"] = id;
    json["plastifierId"] = plastifierId;
    QJsonArray dataAray;
    dataAray.append(plastifier);
    // ToDo: replace with actual value when needed or set null if disgarded in future
    dataAray.append(5000);
    json["data"] = dataAray;
}

void Recipe::onUpdateWithComponentWeightData(int componentId, int weight) {
    switch(componentId) {
        case 1:
            incrementCurrentWeightPlastifier(weight);
            break;
        case 2:
            incrementCurrentWeightWater(weight);
            break;
        default:
            break;
    }
}

