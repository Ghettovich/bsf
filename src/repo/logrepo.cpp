
#include "logrepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include <QtCore/qdatetime.h>

LogRepository::LogRepository() {
    //bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig.database, bsfDbConfig.defaultConnection);
        bsfDb.setDatabaseName(bsfDbConfig.databaseName);
    }
}

void LogRepository::addLog(const BsfLog &log) {
    insert(log);
}

void LogRepository::addLog(const QString &logMsg, LogSeverity logSeverity) {
    BsfLog newLog = BsfLog();
    newLog.log = logMsg;
    newLog.logType = logSeverity;
    insert(newLog);
}

QList<BsfLog> *LogRepository::getBsfLogs() {
    QString queryString = "SELECT id, logtype, log, logdatetime FROM log";
    auto *bsfLogs = new QList<BsfLog>;

    try {
        QSqlQuery query(getQSqlDatabase());

        if (query.exec(queryString)) {
            while (query.next()) {
                BsfLog log = BsfLog();
                log.id = query.value("id").toInt();
                log.logType = query.value("logtype").toInt();
                log.log = query.value("log").toString();
                log.logDateTime = query.value("logdatetime").toInt();
                bsfLogs->append(log);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug(e.what());
    }

    return bsfLogs;
}

void LogRepository::insert(BsfLog log) {
    qDebug("add log called");
    auto *bsfDbconfig = new BsfDbconfig;

    try {
        QSqlDatabase db = QSqlDatabase::database(bsfDbconfig->defaultConnection);

        QSqlQuery query(db);
        if(db.open()) {
            query.prepare("INSERT INTO log (logtype, log, logdatetime) VALUES (:logtype, :log, :logdatetime)");
            query.bindValue(":logtype", log.logType);
            query.bindValue(":log", log.log);
            query.bindValue(":logdatetime", QDateTime::currentSecsSinceEpoch());
            qDebug("add log called with log and severity");
            if (query.exec()) {
                qDebug("added log");
            } else {
                qDebug("failed to execute log query");
            }
            db.close();
        }
    }
    catch (std::exception & e) {
        qDebug(e.what());
    }
}

QSqlDatabase LogRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig.defaultConnection);
}
