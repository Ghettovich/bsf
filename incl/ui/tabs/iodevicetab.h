#ifndef IODEVICETAB_H
#define IODEVICETAB_H

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QUdpSocket>

#include "incl/domain/weightcensor.h"
#include "incl/controller/relaycontroller.h"

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    explicit IODeviceTab(QTabWidget *parent = nullptr);

};
#endif // IODEVICESTAB_H
