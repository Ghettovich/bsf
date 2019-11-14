#ifndef IODEVICETAB_H
#define IODEVICETAB_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>
#include <incl/ui/forms/deviceactionform.h>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    explicit IODeviceTab(QTabWidget *parent = nullptr);

private:
    DeviceActionForm *deviceActionForm = nullptr;
};
#endif // IODEVICESTAB_H
