#ifndef BSF_ACTIONARDUINOREPO_H
#define BSF_ACTIONARDUINOREPO_H

#include <QtSql/QSqlDatabase>
#include <incl/domain/action.h>
#include <incl/data/bsfdatabaseconfig.h>

class ActionArduinoRepository {

public:
    ActionArduinoRepository();
    //QList<ArduinoAction> getArduinoAction();
    QList<Action> getArduinoAction(int arduino_id);
    //QList<ArduinoAction> getArduinoActionWithIODeviceType(int ioDeviceTypeId, int arduinoId);

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
    QList<Action> createActionList(QString &query, int arduino_id = 0);
    //QList<ArduinoAction> createArduinoActionList(QString &query);
    //QList<ArduinoAction> createArduinoIODeviceList(QString &query, int arduino_id, int ioDeviceType = 0);
};
#endif //BSF_ACTIONARDUINOREPO_H
