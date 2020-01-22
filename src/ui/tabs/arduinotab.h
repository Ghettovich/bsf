#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include "ui/forms/deviceform.h"
#include <service/iodeviceservice.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

class ArduinoTab : public QWidget
{
    Q_OBJECT

public:
    ArduinoTab(QWidget *parent, const Qt::WindowFlags &f);

private:
    QHBoxLayout * hbox = nullptr;
    IODeviceService * ioDeviceService;
};

#endif // ARDUINOSTAB_H
