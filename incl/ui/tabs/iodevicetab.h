#ifndef IODEVICETAB_H
#define IODEVICETAB_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>
#include <QHBoxLayout>
//#include <incl/controller/devicecontroller.h>
#include <incl/service/iodeviceservice.h>
#include <incl/ui/forms/deviceactionform.h>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    explicit IODeviceTab(QTabWidget *parent = nullptr);

private:
    QHBoxLayout *hbox = nullptr;
    IODeviceService *ioDeviceService  = nullptr;
    DeviceActionForm *deviceActionForm = nullptr;
    //DeviceController *deviceController = nullptr;
};
#endif // IODEVICESTAB_H
