#ifndef BSF_DEVICECONTROLLER_H
#define BSF_DEVICECONTROLLER_H

#include <QHBoxLayout>
#include <incl/repo/arduinorepo.h>

class DeviceController : public QObject {

public:
    explicit DeviceController();
    void createDeviceWidgets();

    QHBoxLayout *deviceHbox = nullptr;
    QList<Arduino> arduinos;

private:
    ArduinoRepository *arduinoRepository = new ArduinoRepository;

};
#endif //BSF_DEVICECONTROLLER_H
