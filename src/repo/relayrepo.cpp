#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include "relayrepo.h"

RelayRepository::RelayRepository() {
    bsfDbConfig = new BsfDbconfig;
}

QList<Action> RelayRepository::getAllStateActions() {
    QList<Action> stateActions;
    QSqlQuery query(getQSqlDatabase());

    if (query.exec("SELECT * FROM action")) {
        while (query.next()) {
            Action sa;
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
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
