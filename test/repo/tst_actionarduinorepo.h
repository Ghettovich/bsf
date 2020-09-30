#ifndef BSF_TST_ACTIONARDUINOREPO_H
#define BSF_TST_ACTIONARDUINOREPO_H

#include "AutoTest.h"
#include <repo/actionarduinorepo.h>
#include <QtCore/QObject>

class ActionArduinoRepoTest : public QObject {

    Q_OBJECT

private slots:
    void initTestCase();
    void isSizeOfActionListOfArduinoGreaterThanZero();
    void cleanupTestCase();
};


#endif //BSF_TST_ACTIONARDUINOREPO_H
