#ifndef BSF_ACTIONARDUINOREPO_H
#define BSF_ACTIONARDUINOREPO_H

#include <data/bsfdatabaseconfig.h>
#include <domain/action.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class ActionArduinoRepository {

public:
    ActionArduinoRepository();
    QVector<Action> getArduinoAction(int arduino_id);

private:
    BsfDbconfig bsfDbConfig;
};
#endif //BSF_ACTIONARDUINOREPO_H
