#ifndef BSF_LOGSERVICE_H
#define BSF_LOGSERVICE_H

#include <domain/bafalog.h>

class BsfLogService {

public:
    BsfLogService(const QString &_connection = "");
    void addLog(const QString &logMsg, BafaLog::LOG_SEVERITY);
    QVector<BafaLog> getBsfLogList();

private:
    QString connection;
};
#endif //BSF_LOGSERVICE_H
