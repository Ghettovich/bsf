#ifndef BSF_LOGSERVICE_H
#define BSF_LOGSERVICE_H

#include <domain/log.h>

class BsfLogService {

public:
    static void addLog(const BsfLog &log);
    static void addLog(const QString &logMsg, LogSeverity logSeverity);
    static QList<BsfLog> *getBsfLogs();
};
#endif //BSF_LOGSERVICE_H
