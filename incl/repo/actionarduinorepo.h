#ifndef BSF_ACTIONARDUINOREPO_H
#define BSF_ACTIONARDUINOREPO_H

#include <QtSql/QSqlDatabase>
#include <incl/domain/actionarduino.h>
#include <incl/data/bsfdatabaseconfig.h>

class ActionArduinoRepository {

public:
    ActionArduinoRepository();
    QList<Action> getArduinoAction(int arduino_id);
    QList<ArduinoAction> getAllArduinoAction();

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
    QList<Action> createActionList(QString &query, int arduino_id = 0);
    QList<ArduinoAction> createArduinoActionList(QString &query);
};
#endif //BSF_ACTIONARDUINOREPO_H
