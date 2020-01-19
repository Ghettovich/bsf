#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include <QHBoxLayout>
#include <QtWidgets/QWidget>
#include <service/iodeviceservice.h>

class ArduinoTab : public QWidget
{
    Q_OBJECT

public:
    explicit ArduinoTab();

private:
    QHBoxLayout * hbox = nullptr;
    QList<DeviceForm *> arduinoDeviceList;
    IODeviceService *ioDeviceService = nullptr;
};
#endif // ARDUINOSTAB_H
