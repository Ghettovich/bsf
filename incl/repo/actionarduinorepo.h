#ifndef BSF_ACTIONARDUINOREPO_H
#define BSF_ACTIONARDUINOREPO_H

#include <incl/domain/actionarduino.h>
#include <incl/data/bsfdatabaseconfig.h>

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
