#ifndef BSF_RECIPEINFO_H
#define BSF_RECIPEINFO_H

#include <domain/recipe.h>
#include <statemachine/statemachine.h>

struct RecipeInfoData : public EventData {
public:
    Recipe * recipe = nullptr;
};
#endif //BSF_RECIPEINFO_H
