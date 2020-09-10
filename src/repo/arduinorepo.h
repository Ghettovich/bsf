#ifndef BSF_ARDUINOREPO_H
#define BSF_ARDUINOREPO_H

#include <data/bsfdatabaseconfig.h>
#include <domain/arduino.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class ArduinoRepository {

public:
    explicit ArduinoRepository(const QString& connection = "");
    Arduino getArduino(int id);
    Arduino getActiveArduinoWithIODevices(int arduinoId);
    QVector<Arduino> getAllActiveArduino();
    QVector<Arduino *> getAllActiveArduinoWithIODevices();
    void updateArduino(const Arduino& arduinoDevice);

private:
    BsfDbconfig bsfDbConfig;
    IODevice *createIODeviceFromResult(const QSqlQuery&);

};
#endif //BSF_ARDUINOREPO_H
