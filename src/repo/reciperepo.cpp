#include "reciperepo.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>


RecipeRepository::RecipeRepository(const QString &connection) {
    if(!connection.isEmpty()) {
        bsfDbConfig.setDatabaseName(connection);
    }
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

Recipe RecipeRepository::getRecipeWithComponents(int id) {
    Recipe recipe;
    QString queryString = "SELECT r.id, r.description, c.id AS component_id, c.component, rp.target_weight FROM recipe r"
                          "INNER JOIN recipe_components rp ON  r.id = rp.recipe_id "
                          "INNER JOIN component c ON rp.component_id = c.id  "
                          "WHERE r.id =:id ";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", id);
        query.exec();

        if (query.first()) {
            recipe = Recipe(query.value("id").toInt());
            recipe.setDescription(query.value("description").toString());

            while (query.next()) {
                recipe.targetComponentMap.insert(query.value("component_id").toInt(),
                                                 query.value("target_weight").toInt());

                Component component(query.value("component_id").toInt());
                component.setComponent(query.value("component").toString());
                recipe.componentList.append(component);
            }

            return recipe;
        }
    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return Recipe(0);
}

Recipe RecipeRepository::getRecipe(int id) {
    Recipe recipe;
    QString queryString = "SELECT id, description, plastifier, water, sand FROM recipe WHERE id =:id ";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", id);
        query.exec();

        if (query.first()) {
            recipe = Recipe(query.value("id").toInt());
            recipe.setDescription(query.value("description").toString());
            recipe.setPlastifier(query.value("plastifier").toInt());
            recipe.setWater(query.value("water").toInt());
            recipe.setSand(query.value("sand").toInt());
            return recipe;
        }
    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return Recipe(0);
}


