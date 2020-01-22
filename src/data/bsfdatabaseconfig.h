#ifndef BSF_DATABASECONFIG_H
#define BSF_DATABASECONFIG_H

#include <QtCore/QString>

class BsfDbconfig {

public:
    BsfDbconfig();
    QString databaseName = "dbTest.db";
    const QString database = "QSQLITE";
    const QString defaultConnection = "qt_sql_default_connection";

};
#endif //BSF_DATABASECONFIG_H
