#ifndef BSF_TST_RECIPE_H
#define BSF_TST_RECIPE_H

#include "AutoTest.h"
#include <QtCore/QObject>

class RecipeTest : public QObject {
    Q_OBJECT

private:
    bool myCondition ();

private slots:
    void initTestCase();
    void isRecipeTargetMet1();
    void isRecipeTargetMet2();
    void cleanupTestCase();

};

#endif //BSF_TST_RECIPE_H
