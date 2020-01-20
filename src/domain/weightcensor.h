#ifndef WEIGHTCENSOR_H
#define WEIGHTCENSOR_H

#include <domain/iodevice.h>
#include <domain/recipe.h>

class WeightCensor : public IODevice
{

public:
    explicit WeightCensor(int);
    Recipe getRecipe() const;
    void setRecipe(Recipe);
    void updateRecipeWithComponentData(int, int);

private:
    Recipe recipe;
};
#endif // WEIGHTCENSOR_H

