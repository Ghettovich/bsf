#include "logservice.h"
#include <logrepo.h>
#include <QMetaEnum>

BsfLogService::BsfLogService() {
}

void BsfLogService::addLog(const QString &logMsg, BafaLog::LOG_SEVERITY logSeverity) {
    LogRepository logRepository;
    logRepository.addLog(logMsg, logSeverity);
}

QVector<BafaLog> BsfLogService::getBsfLogList() {
    LogRepository logRepository;
    return logRepository.createBsfLogList();
}
