#ifndef BSF_RECIPEREPOTEST_H
#define BSF_RECIPEREPOTEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class RecipeRepoTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void isRecipeFound();
    void isRecipeListEmpty();
    void cleanupTestCase();
};


#endif //BSF_RECIPEREPOTEST_H
