#ifndef BSF_BSFDATABASECONFIG_H
#define BSF_BSFDATABASECONFIG_H

#include <QtCore/QString>

class BsfDbconfig {

public:
    const QString &getDatabase() const;
    const QString &getDatabaseName() const;
    const QString &getDefaultConnection() const;

private:
    const QString database = "QSQLITE";
    const QString databaseName = "../../data/test/dbTest.db";
    const QString defaultConnection = "qt_sql_default_connection";
};
#endif //BSF_BSFDATABASECONFIG_H
