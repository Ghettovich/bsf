#ifndef BSF_ARDUINOREPO_H
#define BSF_ARDUINOREPO_H

#include <domain/arduino.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class ArduinoRepository {

public:
    explicit ArduinoRepository();
    Arduino getArduino(int id);
    Arduino getActiveArduinoWithIODevices(int arduinoId);
    QVector<Arduino> getAllActiveArduino();
    QVector<Arduino *> getAllActiveArduinoWithIODevices();
    void updateArduino(const Arduino& arduinoDevice);

private:
    void setDefaultDatabase(QSqlDatabase&);
    IODevice *createIODeviceFromResult(const QSqlQuery&);

};
#endif //BSF_ARDUINOREPO_H
