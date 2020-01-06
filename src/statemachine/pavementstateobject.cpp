#include "incl/statemachine/pavementstateobject.h"

#include <utility>

PavementStateObject::PavementStateObject() {
}

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
