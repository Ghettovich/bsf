#include "logservicetest.h"
#include <service/logservice.h>
#include <QtTest/QtTest>

DECLARE_TEST_LOGSERVICE(LogServiceTest)

void LogServiceTest::initTestCase() {
}

void LogServiceTest::isLogListGreaterThenZero() {
    QString connectionString = "data/bsfTest.db";
    int logSize = 0;
    BsfLogService logService(connectionString);
    auto logList = logService.getBsfLogList();

    QVERIFY(logList.size() > logSize);
}

void LogServiceTest::isLogListSizeIncreased() {
    QString connectionString = "data/bsfTest.db";
    BsfLogService logService(connectionString);
    auto logList = logService.getBsfLogList();
    int logSize = logList.size();

    logService.addLog("Hoi", BafaLog::INFO);

    logList = logService.getBsfLogList();

    QVERIFY(logList.size() != logSize);
}

void LogServiceTest::cleanupTestCase() {
}
