#include "incl/repo/actionarduinorepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>

ActionArduinoRepository::ActionArduinoRepository() {
    bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
        bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
        qDebug("%s", qUtf8Printable("entered contains"));
    }
}

QList<Action> ActionArduinoRepository::getArduinoAction(int arduino_id) {
    QString query = "SELECT act.id, act.code, act.description "
                    "FROM action act "
                    "INNER JOIN io_device io ON io.action_id = act.id "
                    "WHERE io.arduino_id =:arduino_id "
                    "ORDER BY act.code";


    return createActionList(query, arduino_id);
}

QList<Action> ActionArduinoRepository::createActionList(QString &queryString, int arduino_id) {
    QList<Action> arduinoActions;

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);

        if (arduino_id != 0) {
            query.bindValue(":arduino_id", arduino_id);

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
        qDebug(e.what());
    }

    return arduinoActions;
}

QSqlDatabase ActionArduinoRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
