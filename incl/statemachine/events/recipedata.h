#ifndef BSF_RECIPEDATA_H
#define BSF_RECIPEDATA_H

#include <incl/statemachine/statemachine.h>

struct RecipeData : public EventData {
public:
    int id = 0;
    int weight = 0;
};
#endif //BSF_RECIPEDATA_H
