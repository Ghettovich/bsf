#ifndef BSF_IODEVICESERVICE_H
#define BSF_IODEVICESERVICE_H

#include <QWidget>
#include <incl/controller/devicecontroller.h>

class IODeviceService : public QObject  {

    Q_OBJECT

public:
    explicit IODeviceService(QWidget *parentWidget);

    QList<DeviceForm *> createArduinoDeviceFormList();
    DeviceActionForm *createDeviceActionForm();

private:
    DeviceController *deviceController = nullptr;

};
#endif //BSF_IODEVICESERVICE_H
