#ifndef BSF_ARDUINOREPO_H
#define BSF_ARDUINOREPO_H

#include <QtSql/QSqlDatabase>
#include <incl/domain/arduino.h>
#include <incl/data/bsfdatabaseconfig.h>

//struct Arduino {
//    QString desc;
//    QString ipAddress;
//    QString name;
//
//    qint16 port;
//    int id;
//};

class ArduinoRepository {

public:
    ArduinoRepository();
    QList<Arduino> getAllActiveArduino();
    void updateArduino(const Arduino& arduinoDevice);

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};
#endif //BSF_ARDUINOREPO_H
