#ifndef IODEVICETAB_H
#define IODEVICETAB_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>
#include <incl/controller/devicecontroller.h>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    explicit IODeviceTab(QTabWidget *parent = nullptr);

private:
    DeviceController *deviceController = nullptr;
};
#endif // IODEVICESTAB_H
