#ifndef BSF_ARDUINOREPO_H
#define BSF_ARDUINOREPO_H

#include <domain/arduino.h>
#include <data/bsfdatabaseconfig.h>

class ArduinoRepository {

public:
    ArduinoRepository();
    QList<Arduino> getAllActiveArduino();
    Arduino getArduino(int id);
    void updateArduino(const Arduino& arduinoDevice);

private:
    BsfDbconfig bsfDbConfig;
};
#endif //BSF_ARDUINOREPO_H
