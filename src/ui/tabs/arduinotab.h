#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

class ArduinoTab : public QWidget
{
    Q_OBJECT

public:
    ArduinoTab(QWidget *parent, const Qt::WindowFlags &f);
    void createArduinoDeviceWidgets();

private:
    QHBoxLayout * hbox = nullptr;
};

#endif // ARDUINOSTAB_H
