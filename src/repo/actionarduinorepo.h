#ifndef BSF_ACTIONARDUINOREPO_H
#define BSF_ACTIONARDUINOREPO_H

#include <domain/action.h>
#include <data/bsfdatabaseconfig.h>
#include <QList>
#include <QtSql/QSqlDatabase>

class ActionArduinoRepository {

public:
    ActionArduinoRepository();
    QList<Action> getArduinoAction(int arduino_id);

private:
    BsfDbconfig bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
    QList<Action> createActionList(QString &query, int arduino_id = 0);
};
#endif //BSF_ACTIONARDUINOREPO_H
