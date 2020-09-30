#include "inmemdatabase.h"
#include <QtSql/QSqlQuery>

InMemoryDatabase::InMemoryDatabase() {
}

void InMemoryDatabase::createTestDatabase() {
    dbConfig.setDatabaseName(":memory");
    dbConfig.setSqlDatabase(database);

    QSqlQuery query;

    if(!query.exec("CREATE TABLE IF NOT EXISTS recipe ( "
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "description TEXT NOT NULL DEFAULT '-' )" )) {
        printf("failed to created in RECIPE table for in memory database");
    } else {
        printf("\n\nADDED TABLE!");
    }

    if(!query.exec("CREATE TABLE IF NOT EXISTS state_code ( "
                   " id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   " message TEXT NOT NULL, "
                   " status_message TEXT NOT NULL )")) {
        printf("failed to created in STATECODE table for in memory database");
    }

    if(!query.exec("INSERT INTO state_code (id,message,status_message ) VALUES (0,'READY','Klaar voor gebruik.');")) {
        printf("\nFailed to insert statcode record.");
    }

    if(!query.exec("CREATE TABLE IF NOT EXISTS arduino ( "
                   " id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   " name TEXT NOT NULL, "
                   " ipaddress INTEGER NOT NULL, "
                   " port INTEGER NOT NULL, "
                   " description TEXT DEFAULT '-' )")) {
        printf("failed to created in ARDUINO table for in memory database");
    }

    if(!query.exec("CREATE TABLE IF NOT EXISTS action ( "
                   " id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   " code TEXT NOT NULL UNIQUE, "
                   " description TEXT NOT NULL DEFAULT '-', "
                   " url TEXT )")) {
        printf("failed to created in ACTION table for in memory database");
    }

}

void InMemoryDatabase::insertData() {
    //QSqlQuery query(database);


    //query.exec("INSERT INTO state_code (id,message,status_message) VALUES (1,'LIFT_ASC','Lift gaat omhoog.') ");
    //query.exec("INSERT INTO state_code (id,message,status_message) VALUES (2,'LIFT_DESC','Lift gaat omlaag.') ");
    //query.exec("INSERT INTO state_code (id,message,status_message) VALUES (3,'BIN_LOADING','Bak staat bij de lopende band en staat klaar om gevuld te worden volgens recept.'); ");

}


