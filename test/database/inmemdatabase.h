
#ifndef BSF_INMEMDATABASE_H
#define BSF_INMEMDATABASE_H

#include <data/bsfdatabaseconfig.h>

class InMemoryDatabase {

public:
    InMemoryDatabase();
    void createTestDatabase();
    void insertData();

private:
    BsfDbconfig dbConfig;
    QSqlDatabase database;
};


#endif //BSF_INMEMDATABASE_H
