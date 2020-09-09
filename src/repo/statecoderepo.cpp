#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include <repo/statecoderepo.h>

StateCodeRepository::StateCodeRepository(const QString& _path) {
    path = _path;
}

StateCode StateCodeRepository::getStateCode(int stateCodeId) {
    QString queryString = "SELECT id, message, status_message FROM state_code WHERE id =:id ";

    try {
        QSqlDatabase db;

        bsfDbConfig.setSqlDatabase(db);

        //setDefaultDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", stateCodeId);
        query.exec();

        if (query.first()) {
            StateCode stateCode = StateCode(query.value("id").toInt());
            stateCode.setMessage(query.value("message").toString());
            stateCode.setStatusMessage(query.value("status_message").toString());

            return stateCode;
        }
    } catch (std::exception &e) {
        printf("%s", e.what());
    }

    return StateCode(-1);
}

QVector<StateCode> StateCodeRepository::getStateCodes() {
    QString queryString = "SELECT id, message FROM state_code";
    QVector<StateCode> errorCodes;

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
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

//void StateCodeRepository::setDefaultDatabase(QSqlDatabase &db) {
//    BsfDbconfig dbConfig = BsfDbconfig(path);
//
//    if (!QSqlDatabase::contains(dbConfig.defaultConnection)) {
//        db = QSqlDatabase::addDatabase(dbConfig.database, dbConfig.defaultConnection);
//    } else {
//        db = QSqlDatabase::database(dbConfig.defaultConnection);
//    }
//    db.setDatabaseName(dbConfig.databaseName);
//}
