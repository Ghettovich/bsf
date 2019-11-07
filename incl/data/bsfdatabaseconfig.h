#ifndef BSF_BSFDATABASECONFIG_H
#define BSF_BSFDATABASECONFIG_H

#include <QtCore/QString>

class BsfDbconfig {

public:
    const QString &getDatabase() const {
        return database;
    }

    const QString &getDatabaseName() const {
        return databaseName;
    }

    const QString &getDefaultConnection() const {
        return defaultConnection;
    }

private:
    const QString database = "QSQLITE";
    const QString databaseName = "../test/database/dbTest.db";
    const QString defaultConnection = "qt_sql_default_connection";
};
#endif //BSF_BSFDATABASECONFIG_H
