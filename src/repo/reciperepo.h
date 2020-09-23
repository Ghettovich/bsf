#ifndef BSF_RECIPEREPO_H
#define BSF_RECIPEREPO_H

#include <data/bsfdatabaseconfig.h>
#include <domain/recipe.h>
#include <QtSql/QSqlDatabase>
#include <QtCore/QVector>

class RecipeRepository {

public:
    explicit RecipeRepository(const QString &connection = "");
    Recipe getRecipe(int);
    Recipe getRecipeWithComponents(int);
    QVector<Recipe> getRecipes();


private:
    BsfDbconfig bsfDbConfig;

};
#endif //BSF_RECIPEREPO_H
