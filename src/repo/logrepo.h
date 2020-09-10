#ifndef BSF_LOGREPO_H
#define BSF_LOGREPO_H

#include <data/bsfdatabaseconfig.h>
#include <domain/bafalog.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class LogRepository {

public:
    LogRepository(const QString &connection = "");
    QVector<BafaLog> createBsfLogList();
    void addLog(BafaLog);
    void addLog(const QString &logMsg, BafaLog::LOG_SEVERITY logSeverity);

private:
    BsfDbconfig bsfDbConfig;
    void insert(BafaLog&);

};
#endif //BSF_LOGREPO_H
