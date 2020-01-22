#ifndef BSF_LOGSERVICE_H
#define BSF_LOGSERVICE_H

#include <domain/bafalog.h>

class BsfLogService {

public:
    void addLog(BafaLog &log);
    void addLog(const QString &logMsg, BafaLog::LOG_SEVERITY);
    QVector<BafaLog> getBsfLogList();
};
#endif //BSF_LOGSERVICE_H
