#ifndef BSF_RECIPEREPO_H
#define BSF_RECIPEREPO_H

#include <QtSql/QSqlDatabase>
#include <incl/data/bsfdatabaseconfig.h>
#include <incl/domain/recipe.h>
#include <QtCore/QList>

class RecipeRepository {
public:
    explicit RecipeRepository();
    Recipe * getRecipe(int id);
    QList<Recipe> getRecipes();

private:
    BsfDbconfig *bsfDbConfig = nullptr;
    QSqlDatabase getQSqlDatabase();
};
#endif //BSF_RECIPEREPO_H
