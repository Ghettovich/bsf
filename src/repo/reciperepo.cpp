#include "reciperepo.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>


RecipeRepository::RecipeRepository() {
}

QVector<Recipe> RecipeRepository::getRecipes() {
    QVector<Recipe> recipeList;
    QString queryString = "SELECT id, plastifier_id, sand_id, water_id, description, plastifier, water, sand FROM recipe";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);

        if (query.exec(queryString)) {
            while (query.next()) {
                Recipe recipe = Recipe(query.value("id").toInt());
                recipe.setPlastifierId(query.value("plastifier_id").toInt());
                recipe.setWaterId(query.value("water_id").toInt());
                recipe.setSandId(query.value("sand_id").toInt());
                recipe.setDescription(query.value("description").toString());
                recipe.setPlastifier(query.value("plastifier").toInt());
                recipe.setWater(query.value("water").toInt());
                recipe.setSand(query.value("sand").toInt());
                recipeList.append(recipe);
            }
        }

    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return recipeList;
}

Recipe RecipeRepository::getRecipe(int id) {
    Recipe recipe;
    QString queryString = "SELECT id, description, plastifier, water sand FROM recipe WHERE id =:id";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);

        query.prepare(queryString);
        query.bindValue(":id", id);

        if (query.first()) {
            recipe = Recipe(query.value("id").toInt());
            recipe.setDescription(query.value("description").toString());
            recipe.setPlastifier(query.value("plastifier").toInt());
            recipe.setWater(query.value("water").toInt());
            recipe.setSand(query.value("sand").toInt());
            return recipe;
        } else {
            recipe = Recipe(0);
        }
    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return recipe;
}
