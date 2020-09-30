#ifndef BSF_TST_STATECODEREPO_H
#define BSF_TST_STATECODEREPO_H

#include "AutoTest.h"
#include <database/inmemdatabase.h>
#include <QtCore/QObject>

class StateCodeRepoTest : public QObject {
    Q_OBJECT

private:
    InMemoryDatabase db;

private slots:
    void initTestCase();
    void isStateCodeFound();

    void cleanupTestCase();
};

#endif //BSF_TST_STATECODEREPO_H
