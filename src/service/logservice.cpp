#include "service/logservice.h"
#include <repo/logrepo.h>

void BsfLogService::addLog(const BsfLog &log) {
    auto *logRepository = new LogRepository;
    logRepository->addLog(log);
}

void BsfLogService::addLog(const QString &logMsg, LogSeverity logSeverity) {
    auto *logRepository = new LogRepository;
    logRepository->addLog(logMsg, logSeverity);
}

QList<BsfLog> *BsfLogService::getBsfLogs() {
    auto *logRepository = new LogRepository;
    return logRepository->getBsfLogs();
}
