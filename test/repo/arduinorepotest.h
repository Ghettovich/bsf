#ifndef BSF_ARDUINOREPOTEST_H
#define BSF_ARDUINOREPOTEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class ArduinoRepoTest : public QObject {
    Q_OBJECT


private slots:
    void initTestCase();
    void isArduinoListGreaterThenZero();
    void cleanupTestCase();

};


#endif //BSF_ARDUINOREPOTEST_H
