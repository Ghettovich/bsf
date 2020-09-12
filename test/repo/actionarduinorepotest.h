#ifndef BSF_ACTIONARDUINOREPOTEST_H
#define BSF_ACTIONARDUINOREPOTEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class ActionArduinoRepoTest : public QObject {

    Q_OBJECT

private slots:
    void initTestCase();
    void isSizeOfActionListOfArduinoGreaterThanZero();
    void cleanupTestCase();
};


#endif //BSF_ACTIONARDUINOREPOTEST_H
