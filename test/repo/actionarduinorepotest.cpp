#include "actionarduinorepotest.h"
#include <repo/actionarduinorepo.h>
#include <QtTest/QtTest>

DECLARE_TEST_ACTION_ARDUINO_REPO(ActionArduinoRepoTest)

void ActionArduinoRepoTest::initTestCase() {

}

void ActionArduinoRepoTest::isSizeOfActionListOfArduinoGreaterThanZero() {
    int arduinoId = 1;
    QString connectionString = "data/bsfTest.db";
    ActionArduinoRepository actionArduinoRepository(connectionString);

    QVector<Action> actionList = actionArduinoRepository.getArduinoAction(arduinoId);

    QVERIFY(!actionList.empty());
}

void ActionArduinoRepoTest::cleanupTestCase() {
}