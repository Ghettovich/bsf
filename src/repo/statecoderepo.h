#ifndef BSF_STATECODEREPO_H
#define BSF_STATECODEREPO_H

#include <domain/statecode.h>
#include <data/bsfdatabaseconfig.h>
#include <QtSql/QSqlDatabase>

class StateCodeRepository {

public:
    explicit StateCodeRepository();
    StateCode getStateCode(int);
    QVector<StateCode> getStateCodes();

private:
    BsfDbconfig bsfDbConfig;
    void setDefaultDatabase(QSqlDatabase &db);
};


#endif //BSF_STATECODEREPO_H
