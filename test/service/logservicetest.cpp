#include "logservicetest.h"
#include <service/logservice.h>
#include <QtTest/QtTest>

DECLARE_TEST(LogServiceTest)

void LogServiceTest::initTestCase() {
}

void LogServiceTest::isLogListGreaterThenZero() {
    QString connectionString = "data/bsfTest.db";
    int logSize = 0;
    BsfLogService logService(connectionString);
    auto logList = logService.getBsfLogList();

    // ToDo: replace 0!!
    QVERIFY(logList.size() > logSize);
}

void LogServiceTest::cleanupTestCase() {

}
