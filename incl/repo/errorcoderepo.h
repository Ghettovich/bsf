#ifndef BSF_ERRORCODEREPO_H
#define BSF_ERRORCODEREPO_H

#include <incl/domain/errorcode.h>
#include <incl/data/bsfdatabaseconfig.h>
#include <QtSql/QSqlDatabase>

class ErrorCodeRepository {

public:
    explicit ErrorCodeRepository();
    QList<ErrorCode> getErrorCodes();

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};


#endif //BSF_ERRORCODEREPO_H
