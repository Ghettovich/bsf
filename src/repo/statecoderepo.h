#ifndef BSF_STATECODEREPO_H
#define BSF_STATECODEREPO_H

#include <domain/statecode.h>
#include <data/bsfdatabaseconfig.h>
#include <QtSql/QSqlDatabase>

class StateCodeRepository {

public:
    explicit StateCodeRepository();
    QList<StateCode> getErrorCodes();

private:
    BsfDbconfig bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};


#endif //BSF_STATECODEREPO_H