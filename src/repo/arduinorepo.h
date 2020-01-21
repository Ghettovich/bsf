#ifndef BSF_ARDUINOREPO_H
#define BSF_ARDUINOREPO_H

#include <domain/arduino.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class ArduinoRepository {

public:
    ArduinoRepository();
    QVector<Arduino> getAllActiveArduino();
    Arduino getArduino(int id);
    void updateArduino(const Arduino& arduinoDevice);

private:
    void setDefaultDatabase(QSqlDatabase&);

};
#endif //BSF_ARDUINOREPO_H