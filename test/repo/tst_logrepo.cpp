#include <repo/logrepo.h>
#include "tst_logrepo.h"


DECLARE_TEST_LOG_REPO(LogRepoTest)

void LogRepoTest::initTestCase() {
}

/*
 * Check if log list is not empty.
 * */
void LogRepoTest::isLogListEmpty() {
    // ARRANGE
    const QString testConnection = "/home/mrfunkyman/Documents/databases/bsf/test/bsf.db";
    LogRepository logRepository;

    // ACT
    QVector<BafaLog> logs = logRepository.createBsfLogList();

    // ASSERT
    QVERIFY(!logs.empty());
}

/*
 * Checks wether the log list size is increased after adding a new log.
 * */
void LogRepoTest::isLogListSizeIncreased() {
    // ARRANGE
    const QString testConnection = "/home/mrfunkyman/Documents/databases/bsf/test/bsf.db";
    LogRepository logRepository;

    // ACT
    QVector<BafaLog> logList = logRepository.createBsfLogList();
    logRepository.addLog("Hoi", BafaLog::INFO);
    QVector<BafaLog> secondLogList = logRepository.createBsfLogList();

    // ASSERT
    QVERIFY(secondLogList.size() > logList.size());
}

void LogRepoTest::cleanupTestCase() {
}
