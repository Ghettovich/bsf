#include "incl/data/bsfdatabaseconfig.h"

const QString &BsfDbconfig::getDatabase() const {
    return database;
}

const QString &BsfDbconfig::getDatabaseName() const {
    return databaseName;
}

const QString &BsfDbconfig::getDefaultConnection() const {
    return defaultConnection;
}
