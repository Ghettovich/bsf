#include "actionarduinorepo.h"
#include <data/bsfdatabaseconfig.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>


ActionArduinoRepository::ActionArduinoRepository() {
}

QVector<Action> ActionArduinoRepository::getArduinoAction(int arduino_id) {
    QVector<Action> arduinoActions = QVector<Action>();
    QString queryString = "SELECT act.id, act.code, act.description "
                          "FROM action act "
                          "INNER JOIN io_device io ON io.action_id = act.id "
                          "WHERE io.arduino_id =:arduino_id "
                          "ORDER BY act.code";

    try {
        QSqlDatabase db;
        setDefaultDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":arduino_id", arduino_id);
        query.exec();

        while (query.next()) {
            Action action = Action(query.value("id").toInt());
            action.setCode(query.value("code").toString());
            action.setDescription(query.value("description").toString());
            arduinoActions.append(action);
        }
    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return arduinoActions;
}

void ActionArduinoRepository::setDefaultDatabase(QSqlDatabase db) {
    BsfDbconfig dbConfig = BsfDbconfig();

    if (!QSqlDatabase::contains(dbConfig.defaultConnection)) {
        db = QSqlDatabase::addDatabase(dbConfig.database, dbConfig.defaultConnection);
    }
    else {
        db = QSqlDatabase::database(dbConfig.defaultConnection);
    }
    db.setDatabaseName(dbConfig.databaseName);
}
