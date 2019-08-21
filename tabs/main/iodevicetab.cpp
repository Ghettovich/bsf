#include "headers/tabs/main/iodevicetab.h"
#include <QTabWidget>

IODeviceTab::IODeviceTab(QTabWidget *parent)
    : QTabWidget(parent)
{
    setStatusTip("IO apparaten tab actief");
}
