#ifndef IODEVICETAB_H
#define IODEVICETAB_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>
#include <QHBoxLayout>
#include <service/iodeviceservice.h>
#include <ui/forms/deviceactionform.h>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    explicit IODeviceTab(QTabWidget *parent = nullptr);

private:
    IODeviceService ioDeviceService;
    QHBoxLayout *hbox = nullptr;
    DeviceActionForm *deviceActionForm = nullptr;
    IODeviceForm *ioDeviceForm = nullptr;
};
#endif // IODEVICESTAB_H
