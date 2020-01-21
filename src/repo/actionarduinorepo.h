#ifndef BSF_ACTIONARDUINOREPO_H
#define BSF_ACTIONARDUINOREPO_H

#include <domain/action.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class ActionArduinoRepository {

public:
    ActionArduinoRepository();
    QVector<Action> getArduinoAction(int arduino_id);

private:
    void setDefaultDatabase(QSqlDatabase);
};
#endif //BSF_ACTIONARDUINOREPO_H
