#ifndef BSF_LOGSERVICE_H
#define BSF_LOGSERVICE_H

#include <domain/bafalog.h>

class BsfLogService {

public:
    BsfLogService();
    void addLog(const QString &logMsg, BafaLog::LOG_SEVERITY);
    QVector<BafaLog> getBsfLogList();

private:
    QString connection;
};
#endif //BSF_LOGSERVICE_H
