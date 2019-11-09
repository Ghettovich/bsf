#ifndef BSF_DEVICECONTROLLER_H
#define BSF_DEVICECONTROLLER_H

#include <QtWidgets/QWidget>
#include "incl/repo/arduinorepo.h"

class DeviceController {

public:
    void createDeviceWidgets();
    void updateArduinoDevice(const Arduino &arduinoDevice);

    QHBoxLayout *deviceHbox;
    QList<Arduino> arduinos;

private:
    ArduinoRepository *arduinoRepository = new ArduinoRepository;

};
#endif //BSF_DEVICECONTROLLER_H
