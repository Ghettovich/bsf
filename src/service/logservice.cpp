#include "service/logservice.h"
#include <repo/logrepo.h>

void BsfLogService::addLog(BafaLog &log) {
    auto *logRepository = new LogRepository;
    logRepository->addLog(log);
}

void BsfLogService::addLog(const QString &logMsg, int logSeverity) {
    auto *logRepository = new LogRepository;
    logRepository->addLog(logMsg, logSeverity);
}

QVector<BafaLog> BsfLogService::getBsfLogList() {
    LogRepository logRepository = LogRepository();
    return logRepository.createBsfLogList();
}
