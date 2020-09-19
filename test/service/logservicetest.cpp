#include "logservicetest.h"
#include <service/logservice.h>
#include <QtTest/QtTest>

DECLARE_TEST_LOGSERVICE(LogServiceTest)

void LogServiceTest::initTestCase() {
}

void LogServiceTest::isLogListGreaterThenZero() {
    // ARRANGE
    int logSize = 0;

    // ACT
    BsfLogService logService;
    auto logList = logService.getBsfLogList();

    // ASSERT
    QVERIFY(logList.size() > logSize);
}

void LogServiceTest::isLogListSizeIncreased() {
    // ARRANGE
    BsfLogService logService;
    auto logList = logService.getBsfLogList();

    // ACT
    int logSize = logList.size();
    logService.addLog("Hoi", BafaLog::INFO);
    logList = logService.getBsfLogList();

    // ASSERT
    QVERIFY(logList.size() != logSize);
}

void LogServiceTest::cleanupTestCase() {
}
