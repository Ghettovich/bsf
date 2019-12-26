#ifndef BSF_RECIPE_H
#define BSF_RECIPE_H

#include <QtCore/QString>

class Recipe {

public:
    int getId() const;
    const QString &getDescription() const;
    void setDescription(const QString &_description);
    int getPlastifier() const;
    void setPlastifier(int _plastifier);
    int getWater() const;
    void setWater(int _water);
    int getSand() const;
    void setSand(int _sand);

    bool isPlastifierTargetMet(int target);

private:
    int id = 0;
    QString description;
    int plastifier = 0;
    int water = 0;
    int sand = 0;

};
#endif //BSF_RECIPE_H
