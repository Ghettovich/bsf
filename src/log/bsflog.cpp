#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include <incl/domain/log.h>
#include <incl/log/bsflog.h>
#include <incl/data/bsfdatabaseconfig.h>

BsfLogger::BsfLogger() = default;

void BsfLogger::addLog(const BsfLog &log) {
    qDebug("add log called");
    auto *bsfDbconfig = new BsfDbconfig;
    try {
        QSqlDatabase db = QSqlDatabase::database(bsfDbconfig->getDefaultConnection());

        QSqlQuery query(db);
        if(db.open()) {
            query.prepare("INSERT INTO log (logtype, log, logdatetime) VALUES (:logtype, :log, :logdatetime)");
            query.bindValue(":logtype", log.logType);
            query.bindValue(":log", log.log);
            query.bindValue(":logdatetime", log.logDateTime);
            qDebug("add log called with struct");
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

void BsfLogger::addLog(const QString &log, LogSeverity logSeverity) {
    qDebug("add log called");
    auto *bsfDbconfig = new BsfDbconfig;

    try {
        QSqlDatabase db = QSqlDatabase::database(bsfDbconfig->getDefaultConnection());

        QSqlQuery query(db);
        if(db.open()) {
            query.prepare("INSERT INTO log (logtype, log, logdatetime) VALUES (:logtype, :log, :logdatetime)");
            query.bindValue(":logtype", logSeverity);
            query.bindValue(":log", log);
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
