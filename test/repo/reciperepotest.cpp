#include "reciperepotest.h"
#include <QtTest/QtTest>
#include <repo/reciperepo.h>

DECLARE_TEST_RECIPE_REPO(RecipeRepoTest)

void RecipeRepoTest::initTestCase() {
}

void RecipeRepoTest::isRecipeFound() {
    int recipeId = 1;
    QString connectionString = "data/bsfTest.db";
    RecipeRepository recipeRepository(connectionString);

    Recipe recipe = recipeRepository.getRecipe(recipeId);

    QVERIFY(recipe.getId() > 0);
}

void RecipeRepoTest::isRecipeListEmpty() {
    QString connectionString = "data/bsfTest.db";
    RecipeRepository recipeRepository(connectionString);

    QVector<Recipe> recipeList = recipeRepository.getRecipes();

    QVERIFY(!recipeList.isEmpty());
}

void RecipeRepoTest::cleanupTestCase() {
}
