#ifndef BSF_RECIPEREPO_H
#define BSF_RECIPEREPO_H

#include <domain/recipe.h>
#include <QtSql/QSqlDatabase>
#include <QtCore/QVector>

class RecipeRepository {

public:
    explicit RecipeRepository();
    Recipe getRecipe(int id);
    QVector<Recipe> getRecipes();

private:
    void setDefaultDatabase(QSqlDatabase);

};
#endif //BSF_RECIPEREPO_H
