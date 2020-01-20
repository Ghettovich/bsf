#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include "ui/forms/deviceform.h"
#include "service/iodeviceservice.h"
#include <QtWidgets/QWidget>
#include <QHBoxLayout>
#include <QList>

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
