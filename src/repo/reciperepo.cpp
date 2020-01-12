
#include "incl/repo/reciperepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>


RecipeRepository::RecipeRepository() {
    bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
        bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
    }
}

QList<Recipe> RecipeRepository::getRecipes() {
    QList<Recipe> recipeList;
    QString queryString = "SELECT id, description, plastifier, water, sand FROM recipe";

    try {
        QSqlQuery query(getQSqlDatabase());

        if (query.exec(queryString)) {
            while (query.next()) {
                Recipe recipe = Recipe(query.value("id").toInt());
                recipe.setDescription(query.value("description").toString());
                recipe.setPlastifier(query.value("plastifier").toInt());
                recipe.setWater(query.value("water").toInt());
                recipe.setSand(query.value("sand").toInt());
                recipeList.append(recipe);
            }
        }

    }
    catch (std::exception &e) {
        qDebug(e.what());
    }

    return recipeList;
}

Recipe *RecipeRepository::getRecipe(int id) {
    QString queryString = "SELECT id, description, plastifier, water sand FROM recipe WHERE id =:id";

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);
        query.bindValue(":id", id);

        if (query.first()) {
            auto recipe = new Recipe(query.value("id").toInt());
            recipe->setDescription(query.value("description").toString());
            recipe->setPlastifier(query.value("plastifier").toInt());
            recipe->setWater(query.value("water").toInt());
            recipe->setSand(query.value("sand").toInt());
            return recipe;
        }
    }
    catch (std::exception &e) {
        qDebug(e.what());
    }

    return nullptr;
}


QSqlDatabase RecipeRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
