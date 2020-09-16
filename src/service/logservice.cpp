#include "logservice.h"
#include <repo/logrepo.h>
#include <QMetaEnum>

BsfLogService::BsfLogService(const QString &_connection) {
    if (!_connection.isEmpty()) {
        connection = _connection;
    }
}

void BsfLogService::addLog(BafaLog &log) {
    LogRepository logRepository = LogRepository(connection);
    logRepository.addLog(log);
}

void BsfLogService::addLog(const QString &logMsg, BafaLog::LOG_SEVERITY logSeverity) {
    LogRepository logRepository = LogRepository(connection);
    logRepository.addLog(logMsg, logSeverity);
}

QVector<BafaLog> BsfLogService::getBsfLogList() {
    LogRepository logRepository = LogRepository(connection);
    return logRepository.createBsfLogList();
}
