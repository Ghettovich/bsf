#include "incl/statemachine/pavementstateobject.h"
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

void PavementStateObject::updateIODevicesWithDto(const QList<IODeviceDTO *>& dtoList) {
    qDebug("updateing state object with dto");
    for(auto dev : ioDeviceList) {
        for(auto dto : dtoList) {
            if(dev->getId() == dto->id) {
                printf("found device to update in state object");
                emit dev->deviceStateValueChanged(dto->low == 1 ? IODeviceState::LOW : IODeviceState::HIGH);
            }
        }
    }
}
