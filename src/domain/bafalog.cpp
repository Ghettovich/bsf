#include "bafalog.h"
#include <QMetaEnum>

BafaLog::BafaLog(int id) : id(id) {
    logSeverity = UNKNOWN;
}

int BafaLog::getId() const {
    return id;
}

int BafaLog::getLogType() const {
    return logType;
}

void BafaLog::setLogType(int severity) {
    logType = severity;
}

qint64 BafaLog::getLogDateTime() const {
    return logDateTime;
}

void BafaLog::setLogDateTime(qint64 timestamp) {
    logDateTime = timestamp;
}

QString BafaLog::getLog() const {
    return log;
}

void BafaLog::setLog(const QString &logMessage) {
    log = logMessage;
}

BafaLog::LOG_SEVERITY BafaLog::getLogSeverity() const {
    return logSeverity;
}

void BafaLog::setLogSeverity(BafaLog::LOG_SEVERITY _logSeverity) {
    logSeverity = _logSeverity;
}
