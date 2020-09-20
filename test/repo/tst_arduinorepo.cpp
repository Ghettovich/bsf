#include "tst_arduinorepo.h"
#include <QtTest/QtTest>
#include <repo/arduinorepo.h>

DECLARE_TEST_ARDUINO_REPO(ArduinoRepoTest)

void ArduinoRepoTest::initTestCase() {

}

void ArduinoRepoTest::isActiveArduinoIdNotZero() {
    // ARRANGE
    int arduinoId = 1;
    ArduinoRepository arduinoRepository;

    // ACT
    Arduino arduino = arduinoRepository.getActiveArduinoWithIODevices(arduinoId);

    // ASSERT
    QVERIFY(arduino.getId() != 0);
}

void ArduinoRepoTest::isActiveArduinoListGreaterThenZero() {
    // ARRANGE
    int size = 0;

    ArduinoRepository arduinoRepository;
    // ACT
    QVector<Arduino> arduinoList = arduinoRepository.getAllActiveArduino();

    // ASSERT
    QVERIFY(arduinoList.size() > size);
}

void ArduinoRepoTest::isArduinoFoundWithId() {
    // ARRANGE
    int arduinoId = 2;
    ArduinoRepository arduinoRepository;

    // ACT
    Arduino arduino = arduinoRepository.getArduino(arduinoId);

    // ASSERT
    QVERIFY(arduino.getId() == arduinoId);
}

void ArduinoRepoTest::isArduinoUpdated() {
    // ARRANGE
    int arduinoId = 1;
    QString newValue = "Durp";
    ArduinoRepository arduinoRepository;

    // ACT
    Arduino arduino = arduinoRepository.getArduino(arduinoId);
    arduino.setName(newValue);
    arduinoRepository.updateArduino(arduino);
    arduino = arduinoRepository.getArduino(arduinoId);

    // ASSERT
    QVERIFY(arduino.getName() == newValue);
}

void ArduinoRepoTest::cleanupTestCase() {
}
