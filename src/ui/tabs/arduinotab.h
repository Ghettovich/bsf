#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include <forms/deviceform.h>
#include <iodeviceservice.h>
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
