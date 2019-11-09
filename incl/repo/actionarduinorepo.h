#ifndef BSF_ACTIONARDUINOREPO_H
#define BSF_ACTIONARDUINOREPO_H

#include <incl/data/bsfdatabaseconfig.h>
#include "arduinorepo.h"
#include "relayrepo.h"

struct ArduinoAction {
    int id;
    Action action;
    Arduino arduinoDev;
};

class ActionArduinoRepository {

public:
    ActionArduinoRepository();
    QList<ArduinoAction> getAllArduinoAction();
    QList<ArduinoAction> getAllArduinoAction(int id);

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
    QList<ArduinoAction> createArduinoActionList(QString &query, int id = 0);
};
#endif //BSF_ACTIONARDUINOREPO_H
