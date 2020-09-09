#ifndef BSF_DATABASECONFIG_H
#define BSF_DATABASECONFIG_H

#include <QtCore/QString>
#include <QtSql/QSqlDatabase>

class BsfDbconfig {

public:
    BsfDbconfig();
    BsfDbconfig(const QString&);
    QString databaseName = "dbTest.db";
    const QString database = "QSQLITE";
    const QString defaultConnection = "qt_sql_default_connection";

    void setSqlDatabase(QSqlDatabase&);

};
#endif //BSF_DATABASECONFIG_H
