#ifndef IODEVICETAB_H
#define IODEVICETAB_H

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QUdpSocket>

#include <incl/domain/weightcensor.h>
#include <incl/controller/relaycontroller.h>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    explicit IODeviceTab(QTabWidget *parent = nullptr, QUdpSocket *udpSocket = nullptr);

private slots:
    void btnClickedRequestInfo();
    void broadcastDatagram(QByteArray data, quint16 port);
    void processPendingDatagrams();

private:
    RelayController *relayController = nullptr;

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
    QPlainTextEdit *textEditMsg = nullptr;
    QUdpSocket *udpSocket;
    void createArduinoConfigLayout();
    void createConnectedDevicesLayout();
    void createCensors();
};
#endif // IODEVICESTAB_H
