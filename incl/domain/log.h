#ifndef BSF_LOG_H
#define BSF_LOG_H

#include <QtCore/QString>

struct BsfLog {
    int id;
    int logType;
    qint64 logDateTime;
    QString log;
};

enum LogSeverity {ERROR, WARNING, INFO};
#endif //BSF_LOG_H
