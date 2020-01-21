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
    void createDeviceActionForm(DeviceActionForm *);
    void createIODeviceForm(IODeviceForm *, int);

};
#endif //BSF_DEVICECONTROLLER_H
