#include "tst_recipe.h"
#include <QtTest/QTest>

//DECLARE_TEST_RECIPE(RecipeTest)

void RecipeTest::initTestCase() {
    qDebug("Called before everything else.");
}

void RecipeTest::myFirstTest() {
    QVERIFY(true); // check that a condition is satisfied
    QCOMPARE(1, 1); // compare two values
}

void RecipeTest::mySecondTest() {
    QVERIFY(myCondition());
    QVERIFY(1 != 2);
}

void RecipeTest::cleanupTestCase() {
    qDebug("Called after myFirstTest and mySecondTest.");
}

bool RecipeTest::myCondition() {
    return true;
}
