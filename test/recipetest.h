#ifndef BSF_RECIPETEST_H
#define BSF_RECIPETEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class RecipeTest : public QObject {
    Q_OBJECT

private:
    bool myCondition ();

private slots:
    void initTestCase();
    void myFirstTest();
    void mySecondTest();
    void cleanupTestCase();

};

#endif //BSF_RECIPETEST_H
