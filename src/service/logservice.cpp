#include "service/logservice.h"
#include <repo/logrepo.h>
#include <QMetaEnum>

void BsfLogService::addLog(BafaLog &log) {
    LogRepository logRepository = LogRepository();
    logRepository.addLog(log);
}

void BsfLogService::addLog(const QString &logMsg, BafaLog::LOG_SEVERITY logSeverity) {
    LogRepository logRepository = LogRepository();
    logRepository.addLog(logMsg, logSeverity);
}

QVector<BafaLog> BsfLogService::getBsfLogList() {
    LogRepository logRepository = LogRepository();
    return logRepository.createBsfLogList();
}
