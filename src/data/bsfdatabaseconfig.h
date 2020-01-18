#ifndef BSF_BSFDATABASECONFIG_H
#define BSF_BSFDATABASECONFIG_H

#include <QtCore/QString>

class BsfDbconfig {

public:
    BsfDbconfig();
    QString databaseName = "dbTest.db";
    const QString database = "QSQLITE";
    const QString defaultConnection = "qt_sql_default_connection";

};
#endif //BSF_BSFDATABASECONFIG_H
