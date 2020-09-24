#ifndef BSF_RECIPE_H
#define BSF_RECIPE_H

#include <domain/component.h>
#include <QtCore/QString>
#include <QtCore/QJsonObject>

class Recipe {

public:
    Recipe(int id = 0);
    int getId() const;
    int getActualWeightForComponent(int componentId) const;
    const QString &getDescription() const;
    void setDescription(const QString &_description);
    QVector<Component> componentList;
    QMap<int, int> targetComponentMap;
    QMap<int, int> actualComponentMap;
    void updateWeightForComponent(int, int);
    void initComponentMaps();
    void writeJson(QJsonObject &);
    bool isRecipeTargetMet();

private:
    int id = 0;
    QString description;

};
#endif //BSF_RECIPE_H
