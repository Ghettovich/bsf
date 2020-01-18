#include "pavementstateobject.h"
#include <utility>

PavementStateObject::PavementStateObject() = default;

Recipe *PavementStateObject::getRecipe() const {
    return recipe;
}

void PavementStateObject::setRecipe(Recipe *_recipe) {
    recipe = _recipe;
}

QList<IODevice *> PavementStateObject::getIoDeviceList() const {
    return ioDeviceList;
}

void PavementStateObject::setIoDeviceList(QList<IODevice *> _ioDeviceList) {
    ioDeviceList = std::move(_ioDeviceList);
}

QList<IODevice *> PavementStateObject::getIoDeviceWeightStationList() const {
    return ioDeviceWeightStationList;
}

void PavementStateObject::setIoDeviceListWeightStation(QList<IODevice *> _ioDeviceListWeightStation) {
    ioDeviceWeightStationList = std::move(_ioDeviceListWeightStation);
}

QList<WeightCensor *> PavementStateObject::getWeightSensorList() const {
    return weightSensorList;
}

void PavementStateObject::setWeightSensorList(QList<WeightCensor *> _weightSensorList) {
    weightSensorList = std::move(_weightSensorList);
}

void PavementStateObject::updateIODevicesWithDto(const QList<IODeviceDTO *>& dtoList) {
    qDebug("updateing state object with dto");
    for(auto dev : ioDeviceList) {
        for(auto dto : dtoList) {
            if(dev->getId() == dto->id) {
                // ToDo: re-evaluate this call for sensor form
                emit dev->deviceStateValueChanged(dto->low == 1 ? IODeviceState::LOW : IODeviceState::HIGH);
            }
        }
    }

    for(auto dev : ioDeviceWeightStationList) {
        for(auto dto : dtoList) {
            if(dev->getId() == dto->id) {
                emit dev->deviceStateValueChanged(dto->low == 1 ? IODeviceState::LOW : IODeviceState::HIGH);
            }
        }
    }
}

void PavementStateObject::updateWeightSensorList(int deviceId, int componentId, int newWeight) {
    for(auto dev : weightSensorList) {
        if(dev->getId() == deviceId) {
            emit recipe->updateComponentWithNewWeight(componentId, newWeight);
        }
    }
}
