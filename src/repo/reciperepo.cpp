#include "reciperepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>


RecipeRepository::RecipeRepository() {
    //bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig.database, bsfDbConfig.defaultConnection);
        bsfDb.setDatabaseName(bsfDbConfig.databaseName);
    }
}

QList<Recipe *> RecipeRepository::getRecipes() {
    QList<Recipe *> recipeList;
    QString queryString = "SELECT id, plastifier_id, sand_id, water_id, description, plastifier, water, sand FROM recipe";

    try {
        QSqlQuery query(getQSqlDatabase());

        if (query.exec(queryString)) {
            while (query.next()) {
                auto * recipe = new Recipe(query.value("id").toInt());
                recipe->setPlastifierId(query.value("plastifier_id").toInt());
                recipe->setWaterId(query.value("water_id").toInt());
                recipe->setSandId(query.value("sand_id").toInt());
                recipe->setDescription(query.value("description").toString());
                recipe->setPlastifier(query.value("plastifier").toInt());
                recipe->setWater(query.value("water").toInt());
                recipe->setSand(query.value("sand").toInt());
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
    return QSqlDatabase::database(bsfDbConfig.defaultConnection);
}

