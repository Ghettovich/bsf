#ifndef BSF_ARDUINOREPO_H
#define BSF_ARDUINOREPO_H

#include <QtSql/QSqlDatabase>
#include <incl/domain/arduino.h>
#include <incl/data/bsfdatabaseconfig.h>

class ArduinoRepository {

public:
    ArduinoRepository();
    QList<Arduino> getAllActiveArduino();
    Arduino getArduino(int id);
    void updateArduino(const Arduino& arduinoDevice);

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};
#endif //BSF_ARDUINOREPO_H
