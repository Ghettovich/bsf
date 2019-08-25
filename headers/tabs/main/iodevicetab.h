#ifndef IODEVICETAB_H
#define IODEVICETAB_H

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    IODeviceTab(QTabWidget *parent = nullptr);

private slots:

private:
    QGroupBox *grpboxArduinoConfig;
    QLabel *lblBtnRequestInfo;
    QPushButton *btnRequestInfo;
    QLabel *lblIp;
    QLabel *lblPort;
    QLineEdit *lineEditIp;
    QLineEdit *lineEditPort;
    QGroupBox *grpboxConnectedDevices;
    QLabel *lbldeviceIp;
    QLabel *lblDevicePort;
    QLineEdit *lineEditDeviceIp;
    QLineEdit *lineEditDevicePort;

    void createArduinoConfigLayout();
    void createConnectedDevicesLayout();

};
#endif // IODEVICESTAB_H
