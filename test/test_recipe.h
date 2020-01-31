#ifndef BSF_TEST_RECIPE_H
#define BSF_TEST_RECIPE_H

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
#endif //BSF_TEST_RECIPE_H
