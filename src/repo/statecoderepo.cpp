#include "statecoderepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>

StateCodeRepository::StateCodeRepository() {
    bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
        bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
    }
}

QList<StateCode> StateCodeRepository::getErrorCodes() {
    QString queryString = "SELECT id, message FROM state_code";
    QList<StateCode> errorCodes;

    try {
        QSqlQuery query(getQSqlDatabase());

        if (query.exec(queryString)) {
            while (query.next()) {
                StateCode errorCode = StateCode();
                errorCode.id = query.value("id").toInt();
                errorCode.message = query.value("message").toString();
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug(e.what());
    }

    return errorCodes;
}

QSqlDatabase StateCodeRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
