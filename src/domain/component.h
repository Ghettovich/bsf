#ifndef BSF_COMPONENT_H
#define BSF_COMPONENT_H

#include <QtCore/QString>

class Component {

public:
    explicit Component(int id = 0);
    int getComponentId() const;
    void setComponentId(int _componentId);
    const QString &getComponent() const;
    void setComponent(const QString &_component);
    int getTargetWeight() const;
    void setTargetWeight(int targetWeight);

private:
    int componentId;
    QString component;
    int target_weight;
};


#endif //BSF_COMPONENT_H
