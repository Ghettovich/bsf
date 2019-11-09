#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include "incl/repo/actionarduinorepo.h"

ActionArduinoRepository::ActionArduinoRepository() {
    bsfDbConfig = new BsfDbconfig;
}

QList<ArduinoAction> ActionArduinoRepository::getAllArduinoAction() {
    QString query = "SELECT * FROM action_arduino aa INNER JOIN arduino a on aa.arduino_id = a.id INNER JOIN action a2 on aa.action_id = a2.id";
    return createArduinoActionList(query);
}

QList<ArduinoAction> ActionArduinoRepository::getAllArduinoAction(int id) {
    QString query = "SELECT * FROM action_arduino aa INNER JOIN arduino a on aa.arduino_id = a.id INNER JOIN action a2 on aa.action_id = a2.id WHERE id =:id ";
    return createArduinoActionList(query, id);
}

QSqlDatabase ActionArduinoRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}

QList<ArduinoAction> ActionArduinoRepository::createArduinoActionList(QString &queryString, int id) {
    QList<ArduinoAction> stateActions;
    QSqlQuery query(getQSqlDatabase());

    if(id != 0)
        query.bindValue(":id", id);

    if(query.exec(queryString)) {
        while(query.next()) {
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
            stateActions.append(aa);
        }
    }
    else {
        qDebug("failed to execute getAllArduinoAction");
    }

    return stateActions;
}
