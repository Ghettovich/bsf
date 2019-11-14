#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include <incl/log/bsflog.h>
#include "incl/repo/actionarduinorepo.h"

ActionArduinoRepository::ActionArduinoRepository() {
    bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
        bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
        qDebug("%s", qUtf8Printable("entered contains"));
    }
}

QList<Action> ActionArduinoRepository::getArduinoAction(int arduino_id) {
    QString query = "SELECT aa.id, a.code, a.description FROM action_arduino aa INNER JOIN action a on aa.action_id = a.id WHERE aa.arduino_id=:id";
    return createActionList(query, arduino_id);
}

QList<ArduinoAction> ActionArduinoRepository::getAllArduinoAction() {
    QString query = "SELECT * FROM action_arduino aa INNER JOIN arduino a on aa.arduino_id = a.id INNER JOIN action a2 on aa.action_id = a2.id ORDER BY aa.id";
    return createArduinoActionList(query);
}

QSqlDatabase ActionArduinoRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}

QList<Action> ActionArduinoRepository::createActionList(QString &queryString, int arduino_id) {
    QList<Action> arduinoActions;

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);

        if (arduino_id != 0) {
            query.bindValue(":id", arduino_id);

            if (query.exec()) {
                while (query.next()) {
                    Action action;
                    action.id = query.value("id").toInt();
                    action.code = query.value("code").toString();
                    action.description = query.value("description").toString();
                    arduinoActions.append(action);
                }
                getQSqlDatabase().close();
            }
        } else {
            qDebug("No valid id.. got not get states.");
        }
    } catch (std::exception &e) {
        BsfLogger::addLog(e.what(), LogSeverity::ERROR);
    }

    return arduinoActions;
}

QList<ArduinoAction> ActionArduinoRepository::createArduinoActionList(QString &queryString) {
    QList<ArduinoAction> arduinoStateActions;

    try {
        QSqlQuery query(getQSqlDatabase());

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
            qDebug("%s", qUtf8Printable("failed to execute createArduinoActionList"));
        }
    } catch (std::exception &e) {
        BsfLogger::addLog(e.what(), LogSeverity::ERROR);
    }

    return arduinoStateActions;
}
