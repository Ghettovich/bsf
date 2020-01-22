#ifndef BSF_PAVEMENTSTATEOBJECT_H
#define BSF_PAVEMENTSTATEOBJECT_H

#include <QObject>
#include <domain/recipe.h>

class PavementStateObject {

public:
    PavementStateObject();
    Recipe getRecipe() const;
    void setRecipe(Recipe);
    bool isRecipeTargetMet();

private:
    Recipe recipe;
};

#endif //BSF_PAVEMENTSTATEOBJECT_H
