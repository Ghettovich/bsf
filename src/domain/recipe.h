#ifndef BSF_RECIPE_H
#define BSF_RECIPE_H

#include <QtCore/QString>
#include <QtCore/QJsonObject>

class Recipe {

public:
    Recipe(int id = 0);

    int getId() const;
    const QString &getDescription() const;
    void setDescription(const QString &_description);
    int getPlastifier() const;
    void setPlastifier(int _plastifier);
    int getWater() const;
    void setWater(int _water);
    int getSand() const;
    void setSand(int _sand);
    int getPlastifierId() const;
    void setPlastifierId(int);
    int getWaterId() const;
    void setWaterId(int);
    int getSandId() const;
    void setSandId(int);

    int getCurrentWeightPlastifier() const;
    int getCurrentWeightWater() const;
    int getCurrentWeightSand() const;

    bool isPlastifierTargetMet();
    bool isRecipeTargetMet();

    void initRecipe();
    void incrementCurrentWeightPlastifier(int weight);
    void incrementCurrentWeightWater(int weight);
    void incrementCurrentWeightSand(int weight);
    void updateWeightForComponent(int, int);
    void writeJson(QJsonObject &);

private:
    int id = 0, plastifierId = 0, waterId = 0, sandId = 0;
    int plastifier = 0, currentWeightPlastifier = 0;
    int water = 0, currentWeightWater = 0;
    int sand = 0, currentWeightSand = 0;
    QString description;

};
#endif //BSF_RECIPE_H
