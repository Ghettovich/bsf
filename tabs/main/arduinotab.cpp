#include "headers/tabs/main/arduinotab.h"
#include <QTabWidget>

ArduinoTab::ArduinoTab(QTabWidget *parent)
    : QTabWidget(parent)
{
    setStatusTip(tr("Arduino tab actief"));
}
