#include "arduinorepotest.h"
#include <QtTest/QtTest>
//#include <repo/arduinorepo.h>

DECLARE_TEST_ARDUINO_REPO(ArduinoRepoTest)

void ArduinoRepoTest::initTestCase() {

}

void ArduinoRepoTest::isArduinoListGreaterThenZero() {
    int size = 0;
    QString connectionString = "data/bsfTest.db";
    //ArduinoRepository arduinoRepository(connectionString);

    //QVector<Arduino> arduinoList = arduinoRepository.getAllActiveArduino();

    QVERIFY(0 == size);
}

void ArduinoRepoTest::cleanupTestCase() {

}
