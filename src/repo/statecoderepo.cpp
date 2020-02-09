#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include <repo/statecoderepo.h>

StateCodeRepository::StateCodeRepository() {
    //bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig.database, bsfDbConfig.defaultConnection);
        bsfDb.setDatabaseName(bsfDbConfig.databaseName);
    }
}

QList<StateCode> StateCodeRepository::getErrorCodes() {
    QString queryString = "SELECT id, message FROM state_code";
    QList<StateCode> errorCodes;

    try {
        QSqlDatabase db;
        setDefaultDatabase(db);
        QSqlQuery query(db);

        query.exec(queryString);
        while (query.next()) {
            StateCode errorCode = StateCode(query.value("id").toInt());
            errorCode.setMessage(query.value("message").toString());
        }

    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return errorCodes;
}

void StateCodeRepository::setDefaultDatabase(QSqlDatabase &db) {
    BsfDbconfig dbConfig = BsfDbconfig();

    if (!QSqlDatabase::contains(dbConfig.defaultConnection)) {
        db = QSqlDatabase::addDatabase(dbConfig.database, dbConfig.defaultConnection);
    } else {
        db = QSqlDatabase::database(dbConfig.defaultConnection);
    }
    db.setDatabaseName(dbConfig.databaseName);
}