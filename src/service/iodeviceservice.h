#ifndef BSF_IODEVICESERVICE_H
#define BSF_IODEVICESERVICE_H

#include <QWidget>
#include <controller/device/devicecontroller.h>
#include <ui/forms/deviceform.h>
#include <ui/forms/deviceactionform.h>

class IODeviceService : public QObject  {

    Q_OBJECT

public:
    explicit IODeviceService();

    QList<DeviceForm *> createArduinoDeviceWidgetList(QWidget *parent);
    DeviceActionForm * createDeviceActionForm(QWidget *parent);
    IODeviceForm * createIODeviceForm(QWidget *parent);

private:
    DeviceController *deviceController = nullptr;

};
#endif //BSF_IODEVICESERVICE_H
