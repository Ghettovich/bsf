#ifndef BSF_DEVICECONTROLLER_H
#define BSF_DEVICECONTROLLER_H

#include <repo/arduinorepo.h>
#include <ui/forms/deviceform.h>
#include <ui/forms/deviceactionform.h>

class DeviceController : public QObject {

public:
    explicit DeviceController();
    QList<DeviceForm *> createDeviceWidgets(QWidget *parent);
    DeviceActionForm *createDeviceActionForm(QWidget *parent);
    IODeviceForm *createIODeviceForm(QWidget *parent);


private:
    ArduinoRepository *arduinoRepository = nullptr;
};
#endif //BSF_DEVICECONTROLLER_H
