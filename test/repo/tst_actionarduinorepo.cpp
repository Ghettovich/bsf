#include "tst_actionarduinorepo.h"
#include <QtTest/QtTest>

DECLARE_TEST_ACTION_ARDUINO_REPO(ActionArduinoRepoTest)

void ActionArduinoRepoTest::initTestCase() {

}

/*
 * Checks if the received list is not empty.
 * */
void ActionArduinoRepoTest::isSizeOfActionListOfArduinoGreaterThanZero() {
    // ARRANGE
    int arduinoId = 1;
    ActionArduinoRepository actionArduinoRepository;

    // ACT
    QVector<Action> actionList = actionArduinoRepository.getArduinoAction(arduinoId);

    // ASSERT
    QVERIFY(!actionList.empty());
}

void ActionArduinoRepoTest::cleanupTestCase() {
}