#ifndef BSF_RECIPEINFO_H
#define BSF_RECIPEINFO_H

#include <recipe.h>
#include <statemachine.h>

struct RecipeInfoData : public EventData {
public:
    Recipe recipe = Recipe(0);
};
#endif //BSF_RECIPEINFO_H
