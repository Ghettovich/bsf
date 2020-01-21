#ifndef BSF_IODEVICESERVICE_H
#define BSF_IODEVICESERVICE_H

#include <controller/device/devicecontroller.h>
#include <ui/forms/deviceform.h>
#include <ui/forms/deviceactionform.h>
#include <QWidget>

class IODeviceService : public QObject  {

    Q_OBJECT

public:
    explicit IODeviceService(QObject *parent);

    QList<DeviceForm *> createArduinoDeviceWidgetList(QWidget *parent);
    void createDeviceActionForm(DeviceActionForm *parent);
    void createIODeviceForm(IODeviceForm *, int);

private:
    DeviceController *deviceController = nullptr;

};
#endif //BSF_IODEVICESERVICE_H
