#ifndef BSF_DEVICECONTROLLER_H
#define BSF_DEVICECONTROLLER_H

#include <incl/repo/arduinorepo.h>
#include <incl/ui/forms/deviceform.h>
#include <incl/ui/forms/deviceactionform.h>

class DeviceController : public QObject {

public:
    explicit DeviceController(QWidget *parent);
    QList<DeviceForm *> createDeviceWidgets();
    DeviceActionForm *createDeviceActionForm();
    QList<Arduino> arduinos;
    QWidget *parentWidget = nullptr;

private:
    ArduinoRepository *arduinoRepository = nullptr;
};
#endif //BSF_DEVICECONTROLLER_H
