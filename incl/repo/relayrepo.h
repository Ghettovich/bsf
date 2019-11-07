#ifndef BSF_RELAYREPO_H
#define BSF_RELAYREPO_H

#include <QtCore/QList>
#include <QtSql/QSqlDatabase>
#include <incl/data/bsfdatabaseconfig.h>

struct stateAction {
    int id;
    QString code;
    QString description;
};

class RelayRepository {

public:
    RelayRepository();
    QList<stateAction> getAllStateActions();

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};
#endif //BSF_RELAYREPO_H
