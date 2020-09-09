#include "data/bsfdatabaseconfig.h"

BsfDbconfig::BsfDbconfig() {
    databaseName = "data/bsf.db";
}

BsfDbconfig::BsfDbconfig(const QString &_databaseName) {
    databaseName = _databaseName;
}

void BsfDbconfig::setSqlDatabase(QSqlDatabase &db) {

    if (!QSqlDatabase::contains(defaultConnection)) {
        db = QSqlDatabase::addDatabase(database, defaultConnection);
    } else {
        db = QSqlDatabase::database(defaultConnection);
    }
    db.setDatabaseName(databaseName);
}
