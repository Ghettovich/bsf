#include "arduinorepotest.h"
#include <QtTest/QtTest>
#include <repo/arduinorepo.h>

DECLARE_TEST_ARDUINO_REPO(ArduinoRepoTest)

void ArduinoRepoTest::initTestCase() {

}

void ArduinoRepoTest::isActiveArduinoIdNotZero() {
    int arduinoId = 1;
    QString connectionString = "data/bsfTest.db";
    ArduinoRepository arduinoRepository(connectionString);
    Arduino arduino = arduinoRepository.getActiveArduinoWithIODevices(arduinoId);

    QVERIFY(arduino.getId() != 0);
}

void ArduinoRepoTest::isActiveArduinoListGreaterThenZero() {
    int size = 0;
    QString connectionString = "data/bsfTest.db";
    ArduinoRepository arduinoRepository(connectionString);
    QVector<Arduino> arduinoList = arduinoRepository.getAllActiveArduino();

    QVERIFY(arduinoList.size() > size);
}

void ArduinoRepoTest::isArduinoFoundWithId() {
    int arduinoId = 2;
    QString connectionString = "data/bsfTest.db";
    ArduinoRepository arduinoRepository(connectionString);

    Arduino arduino = arduinoRepository.getArduino(arduinoId);

    QVERIFY(arduino.getId() == arduinoId);
}

void ArduinoRepoTest::isArduinoUpdated() {
    int arduinoId = 1;
    QString newValue = "Durp";
    QString connectionString = "data/bsfTest.db";
    ArduinoRepository arduinoRepository(connectionString);

    Arduino arduino = arduinoRepository.getArduino(arduinoId);
    arduino.setName(newValue);
    arduinoRepository.updateArduino(arduino);

    arduino = arduinoRepository.getArduino(arduinoId);

    QVERIFY(arduino.getName() == newValue);
}

void ArduinoRepoTest::cleanupTestCase() {
}
