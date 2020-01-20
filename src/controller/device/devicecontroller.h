#ifndef BSF_DEVICECONTROLLER_H
#define BSF_DEVICECONTROLLER_H

#include <QObject>
#include <ui/forms/deviceform.h>
#include <ui/forms/deviceactionform.h>
#include <ui/forms/iodeviceform.h>

class DeviceController : public QObject {

    Q_OBJECT

public:
    explicit DeviceController(QObject *parent);

    QList<DeviceForm *> createDeviceWidgets(QWidget *parent);
    DeviceActionForm *createDeviceActionForm(QWidget *parent);
    IODeviceForm *createIODeviceForm(QWidget *parent);

private:
    //ArduinoRepository arduinoRepository;
    //ActionArduinoRepository actionArduinoRepository;

};
#endif //BSF_DEVICECONTROLLER_H
