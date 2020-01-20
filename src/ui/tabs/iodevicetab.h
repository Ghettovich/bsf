#ifndef BSF_IODEVICETAB_H
#define BSF_IODEVICETAB_H

#include <ui/forms/deviceactionform.h>
#include <service/iodeviceservice.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    explicit IODeviceTab();

private:
    IODeviceForm *ioDeviceForm = nullptr;
    DeviceActionForm *deviceActionForm = nullptr;
    IODeviceService ioDeviceService;
    QHBoxLayout *hbox = nullptr;
};
#endif // BSF_IODEVICESTAB_H
