#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include "relayrepo.h"

RelayRepository::RelayRepository() {
    bsfDbConfig = new BsfDbconfig;
//    auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
//    bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
//
//    if (!bsfDb.open()) {
//        qDebug("could not open bsfDb");
//    } else {
//        qDebug("Opened bsfDb");
//    }
}

QList<stateAction> RelayRepository::getAllStateActions() {
    QList<stateAction> stateActions;
    QSqlQuery query(getQSqlDatabase());

    if (query.exec("SELECT * FROM action")) {
        while (query.next()) {
            stateAction sa;
            sa.id = query.value("id").toInt();
            sa.code = query.value("code").toString();
            sa.description = query.value("description").toString();
            stateActions.append(sa);
        }
        getQSqlDatabase().close();
    } else {
        qDebug("failed to execute get all state actions");
    }

    return stateActions;
}

QSqlDatabase RelayRepository::getQSqlDatabase() {
    return QSqlDatabase::database("qt_sql_default_connection");
}
