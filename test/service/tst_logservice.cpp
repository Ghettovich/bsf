#include "tst_logservice.h"
#include <service/logservice.h>
#include <QtTest/QtTest>

DECLARE_TEST_LOGSERVICE(LogServiceTest)

void LogServiceTest::initTestCase() {
}

/*
 * Check if log list is not empty.
 * */
void LogServiceTest::isLogListNotEmpty() {
    // ARRANGE
    BsfLogService logService;

    // ACT
    auto logList = logService.getBsfLogList();

    // ASSERT
    QVERIFY(!logList.isEmpty());
}

/*
 * Checks wether the log list size is increased after adding a new log.
 * */
void LogServiceTest::isLogListSizeIncreased() {
    // ARRANGE
    BsfLogService logService;
    auto logList = logService.getBsfLogList();

    // ACT
    logService.addLog("Hoi", BafaLog::INFO);
    auto secondLogList = logService.getBsfLogList();

    // ASSERT
    QVERIFY(secondLogList.size() > logList.size());
}

void LogServiceTest::cleanupTestCase() {
}
