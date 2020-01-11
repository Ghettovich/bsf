#ifndef BSF_RECIPEINFO_H
#define BSF_RECIPEINFO_H

#include <incl/domain/recipe.h>
#include <incl/statemachine/statemachine.h>

struct RecipeInfoData : public EventData {
public:
    Recipe * recipe = nullptr;
};
#endif //BSF_RECIPEINFO_H
