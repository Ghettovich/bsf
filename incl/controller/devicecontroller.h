#ifndef BSF_DEVICECONTROLLER_H
#define BSF_DEVICECONTROLLER_H

#include <QtWidgets/QWidget>
#include <incl/repo/arduinorepo.h>

class DeviceController {

public:
    void createDeviceWidgets();
    void updateArduinoDevice(const arduino &arduinoDevice);

    QHBoxLayout *deviceHbox;
    QList<arduino> arduinos;

private:
    ArduinoRepository *arduinoRepository = new ArduinoRepository;

};
#endif //BSF_DEVICECONTROLLER_H
