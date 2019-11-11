#ifndef BSF_BSFLOG_H
#define BSF_BSFLOG_H

#include <QtCore/QString>
#include <QtSql/QSqlDatabase>
#include <QtCore/qdatetime.h>

struct BsfLog {
    int id;
    int logType;
    int logDateTime;
    QString log;
};

enum LogSeverity {ERROR, WARNING, INFO};

class BsfLogger {
public:
    static void addLog(const BsfLog &log);
    static void addLog(const QString &log, LogSeverity logSeverity);
private:
    BsfLogger();
};
#endif //BSF_BSFLOG_H
