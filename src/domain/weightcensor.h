#ifndef WEIGHTCENSOR_H
#define WEIGHTCENSOR_H

#include "iodevice.h"
#include "recipe.h"

class WeightCensor : public IODevice
{
    Q_OBJECT

public:
    explicit WeightCensor(int);

    const Recipe *getRecipe() const;
    void setRecipe(Recipe *_recipe);

signals:
    void updateRecipeWithComponentData(int, int);

private:
    Recipe * recipe = nullptr;
};
#endif // WEIGHTCENSOR_H

