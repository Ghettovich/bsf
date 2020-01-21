#include "logrepo.h"
#include <data/bsfdatabaseconfig.h>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtCore/QDateTime>
#include <utility>

LogRepository::LogRepository() {
}

void LogRepository::addLog(BafaLog _log) {
    insert(std::move(_log));
}

void LogRepository::addLog(const QString &logMsg, int logSeverity) {
    BafaLog newLog = BafaLog();
    newLog.setLog(logMsg);
    newLog.setLogType(logSeverity);
    insert(newLog);
}

QVector<BafaLog> LogRepository::createBsfLogList() {
    QVector<BafaLog> logList = QVector<BafaLog>();
    QString queryString = "SELECT id, logtype, log, logdatetime FROM log";

    try {
        QSqlDatabase db;
        setDefaultDatabase(db);
        QSqlQuery q(db);

        db.open();
        q.exec(queryString);

        while (q.next()) {
            qDebug("got log");
            BafaLog log = BafaLog(q.value("id").toInt());
            log.setLogType(q.value("logtype").toInt());
            log.setLog(q.value("log").toString());
            log.setLogDateTime(q.value("logdatetime").toInt());
            log.setLogSeverity(BafaLog::LOG_SEVERITY(log.getLogType()));
            logList.append(log);
        }

        db.close();

    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return logList;
}

void LogRepository::insert(BafaLog _log) {
    qDebug("add log called");
    BafaLog log = std::move(_log);
    BsfDbconfig bsfDbconfig = BsfDbconfig();

    try {
        QSqlDatabase db;
        setDefaultDatabase(db);
        QSqlQuery query(db);

        if (db.open()) {
            query.prepare("INSERT INTO log (logtype, log, logdatetime) VALUES (:logtype, :log, :logdatetime)");
            query.bindValue(":logtype", log.getLogType());
            query.bindValue(":log", log.getLog());
            query.bindValue(":logdatetime", QDateTime::currentSecsSinceEpoch());
            qDebug("add log called with log and severity");
            if (query.exec()) {
                qDebug("added log");
            }
        }
        db.close();
    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }
}

void LogRepository::setDefaultDatabase(QSqlDatabase db) {
    BsfDbconfig dbConfig = BsfDbconfig();

    if (!QSqlDatabase::contains(dbConfig.defaultConnection)) {
        db = QSqlDatabase::addDatabase(dbConfig.database, dbConfig.defaultConnection);
    } else {
        qDebug("set database name");
        db = QSqlDatabase::database(dbConfig.defaultConnection);
    }
    db.setDatabaseName(dbConfig.databaseName);
}
