#ifndef BSF_DEVICECONTROLLER_H
#define BSF_DEVICECONTROLLER_H

#include <ui/forms/deviceform.h>
#include <ui/forms/deviceactionform.h>
#include <ui/forms/iodeviceform.h>

class DeviceController : public QObject {

public:
    explicit DeviceController();
    QList<DeviceForm *> createDeviceWidgets(QWidget *parent);
    DeviceActionForm *createDeviceActionForm(QWidget *parent);
    IODeviceForm *createIODeviceForm(QWidget *parent);

private:
    //ArduinoRepository arduinoRepository;
    //ActionArduinoRepository actionArduinoRepository;

};
#endif //BSF_DEVICECONTROLLER_H
