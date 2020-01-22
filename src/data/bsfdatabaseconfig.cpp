
#include "data/bsfdatabaseconfig.h"
#include <QDir>

//QString BsfDbconfig::getDatabase() const {
//    return database;
//}
//
//QString BsfDbconfig::getDatabaseName() const {
//    return databaseName;
//}
//
//QString BsfDbconfig::getDefaultConnection() const {
//    return defaultConnection;
//}
BsfDbconfig::BsfDbconfig() {
    databaseName = R"(C:\testrepo\data\test\dbTest.db)";
    qDebug("%s", qUtf8Printable(QDir::current().path()));
    qDebug("%s", qUtf8Printable(databaseName));



}
