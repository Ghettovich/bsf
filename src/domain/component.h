#ifndef BSF_COMPONENT_H
#define BSF_COMPONENT_H

#include <QtCore/QString>

class Component {

public:
    Component(int id = 0);
    int getComponentId() const;
    void setComponentId(int _componentId);
    const QString &getComponent() const;
    void setComponent(const QString &_component);

private:
    int componentId;
    QString component;
};


#endif //BSF_COMPONENT_H
