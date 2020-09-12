#ifndef BSF_STATECODEREPOTEST_H
#define BSF_STATECODEREPOTEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class StateCodeRepoTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void isStateCodeFound();

    void cleanupTestCase();
};

#endif //BSF_STATECODEREPOTEST_H
