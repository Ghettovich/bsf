#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include <QTabWidget>
#include <incl/controller/devicecontroller.h>

class ArduinoTab : public QWidget
{
    Q_OBJECT

public:
    explicit ArduinoTab(QTabWidget *parent = nullptr);

private:
    DeviceController *deviceController = nullptr;
};
#endif // ARDUINOSTAB_H
