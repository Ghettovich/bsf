#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include <incl/log/bsflog.h>
#include "incl/repo/actionarduinorepo.h"

ActionArduinoRepository::ActionArduinoRepository() {
    bsfDbConfig = new BsfDbconfig;
    qDebug("%s", qUtf8Printable(bsfDbConfig->getDefaultConnection()));
    qDebug("%s", qUtf8Printable(bsfDbConfig->getDatabaseName()));
    qDebug("%s", qUtf8Printable(bsfDbConfig->getDatabase()));
    if(!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
        bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
        qDebug("%s", qUtf8Printable("entered contains"));
    }
}

QList<ArduinoAction> ActionArduinoRepository::getAllArduinoAction() {
    qDebug("%s", qUtf8Printable("entered getAllArduinoAction"));
//    qDebug("%s", qUtf8Printable(bsfDbConfig.getDatabaseName()));
//    qDebug("%s", qUtf8Printable(getQSqlDatabase().driverName()));

    QString query = "SELECT * FROM action_arduino aa INNER JOIN arduino a on aa.arduino_id = a.id INNER JOIN action a2 on aa.action_id = a2.id ORDER BY aa.id";
    return createArduinoActionList(query);
}

QList<ArduinoAction> ActionArduinoRepository::getAllArduinoAction(int id) {
    QString query = "SELECT * FROM action_arduino aa INNER JOIN arduino a on aa.arduino_id = a.id INNER JOIN action a2 on aa.action_id = a2.id WHERE id =:id ";
    return createArduinoActionList(query, id);
}

QSqlDatabase ActionArduinoRepository::getQSqlDatabase() {
    return QSqlDatabase::database("qt_sql_default_connection");
}

QList<ArduinoAction> ActionArduinoRepository::createArduinoActionList(QString &queryString, int id) {
    qDebug("entered create arduino action list...");
    QList<ArduinoAction> arduinoStateActions;

    try {
        qDebug("getting QSql database...");
        QSqlQuery query(getQSqlDatabase());

        qDebug("creating arduino action list...");

        if (id != 0)
            query.bindValue(":id", id);

        if (query.exec(queryString)) {
            while (query.next()) {
                ArduinoAction aa;
                aa.id = query.value("id").toInt();
                aa.arduinoDev.desc = query.value("description").toString();
                aa.arduinoDev.id = query.value("arduino_id").toInt();
                aa.arduinoDev.ipAddress = query.value("ipaddress").toString();
                aa.arduinoDev.name = query.value("name").toString();
                aa.arduinoDev.port = query.value("port").toInt();
                aa.action.id = query.value("action_id").toInt();
                aa.action.code = query.value("code").toString();
                aa.action.description = query.value("description").toString();
                arduinoStateActions.append(aa);
            }
            getQSqlDatabase().close();
        } else {
            qDebug("failed to execute getAllArduinoAction");
        }
    } catch (std::exception & e) {
        BsfLogger::addLog(e.what(), LogSeverity::ERROR);
    }

    return arduinoStateActions;
}
