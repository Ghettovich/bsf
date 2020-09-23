
#include "component.h"

Component::Component(int id) : componentId(id) {
}

int Component::getComponentId() const {
    return componentId;
}

void Component::setComponentId(int _componentId) {
    Component::componentId = _componentId;
}

const QString &Component::getComponent() const {
    return component;
}

void Component::setComponent(const QString &_component) {
    Component::component = _component;
}

int Component::getTargetWeight() const {
    return target_weight;
}

void Component::setTargetWeight(int _targetWeight) {
    target_weight = _targetWeight;
}
