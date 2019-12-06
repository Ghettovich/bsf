#include "errorcoderepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>

ErrorCodeRepository::ErrorCodeRepository() {
    bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
        bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
    }
}

QList<ErrorCode> ErrorCodeRepository::getErrorCodes() {
    QString queryString = "SELECT id, message FROM error_code";
    QList<ErrorCode> errorCodes;

    try {
        QSqlQuery query(getQSqlDatabase());

        if (query.exec(queryString)) {
            while (query.next()) {
                ErrorCode errorCode = ErrorCode();
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

QSqlDatabase ErrorCodeRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
