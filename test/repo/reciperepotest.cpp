#include "reciperepotest.h"
#include <QtTest/QtTest>
#include <repo/reciperepo.h>

DECLARE_TEST_RECIPE_REPO(RecipeRepoTest)

void RecipeRepoTest::initTestCase() {
}

void RecipeRepoTest::isRecipeFound() {
    // ARRANGE
    int recipeId = 1;
    RecipeRepository recipeRepository;

    // ACT
    Recipe recipe = recipeRepository.getRecipe(recipeId);

    // ASSERT
    QVERIFY(recipe.getId() > 0);
}

void RecipeRepoTest::isRecipeListEmpty() {
    // ARRANGE
    RecipeRepository recipeRepository;

    // ACT
    QVector<Recipe> recipeList = recipeRepository.getRecipes();

    // ASSERT
    QVERIFY(!recipeList.isEmpty());
}

void RecipeRepoTest::cleanupTestCase() {
}
