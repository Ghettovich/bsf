#ifndef BSF_STATECODEREPO_H
#define BSF_STATECODEREPO_H

#include <domain/statecode.h>
#include <data/bsfdatabaseconfig.h>
#include <QtSql/QSqlDatabase>

class StateCodeRepository {

public:
    explicit StateCodeRepository(const QString&);
    StateCode getStateCode(int);

private:
    BsfDbconfig bsfDbConfig;
};


#endif //BSF_STATECODEREPO_H
