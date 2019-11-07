#ifndef BSF_ARDUINOREPO_H
#define BSF_ARDUINOREPO_H

#include <QtSql/QSqlDatabase>
#include <incl/data/bsfdatabaseconfig.h>

struct arduino {
    QString desc;
    QString ipAddress;
    QString name;

    qint16 port;
    int id;
};

class ArduinoRepository {

public:
    ArduinoRepository();
    QList<arduino> getAllActiveArduino();
    void updateArduino(const arduino& arduinoDevice);

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};
#endif //BSF_ARDUINOREPO_H
