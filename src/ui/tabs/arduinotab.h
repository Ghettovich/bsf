#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include "ui/forms/deviceform.h"
#include "service/iodeviceservice.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

class ArduinoTab : public QWidget
{
    Q_OBJECT

public:
    explicit ArduinoTab(QWidget *parent);

private:
    QHBoxLayout * hbox = nullptr;
    QList<DeviceForm *> arduinoDeviceList;
    IODeviceService * ioDeviceService;
};
#endif // ARDUINOSTAB_H
