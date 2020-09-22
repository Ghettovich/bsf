#include "tst_recipe.h"
#include <QtTest/QTest>
#include <repo/reciperepo.h>

DECLARE_TEST_RECIPE(RecipeTest)

void RecipeTest::initTestCase() {
}

/*
 * Increases and decreased weight to a recipe and check if target is met.
 * Default target values should be: 50 plastifier, 500 water and 500 sand.
 * */
void RecipeTest::isRecipeTargetMet1() {
    int recipeId = 1;
    RecipeRepository recipeRepository;
    Recipe recipe = recipeRepository.getRecipe(recipeId);

    recipe.updateCurrentWeightPlastifier(50);
    recipe.updateCurrentWeightWater(500);

    QVERIFY(!recipe.isRecipeTargetMet());

    recipe.updateCurrentWeightSand(500);

    QVERIFY(recipe.isRecipeTargetMet());
}

void RecipeTest::isRecipeTargetMet2() {
    int recipeId = 1;
    RecipeRepository recipeRepository;
    Recipe recipe = recipeRepository.getRecipe(recipeId);

    recipe.updateCurrentWeightPlastifier(100);
    recipe.updateCurrentWeightWater(450);

    QVERIFY(!recipe.isRecipeTargetMet());

    recipe.updateCurrentWeightSand(2000);

    QVERIFY(!recipe.isRecipeTargetMet());

    recipe.updateCurrentWeightPlastifier(50);
    recipe.updateCurrentWeightSand(500);

    QVERIFY(!recipe.isRecipeTargetMet());

    recipe.updateCurrentWeightWater(500);

    QVERIFY(recipe.isRecipeTargetMet());
}

void RecipeTest::cleanupTestCase() {
}
