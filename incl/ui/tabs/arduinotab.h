#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>
#include <incl/service/iodeviceservice.h>

class ArduinoTab : public QWidget
{
    Q_OBJECT

public:
    explicit ArduinoTab(QTabWidget *parent = nullptr);

private:
    QHBoxLayout * hbox = nullptr;
    QList<DeviceForm *> arduinoDeviceList;
    IODeviceService *ioDeviceService = nullptr;
};
#endif // ARDUINOSTAB_H
