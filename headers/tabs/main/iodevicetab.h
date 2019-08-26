#ifndef IODEVICETAB_H
#define IODEVICETAB_H

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QUdpSocket>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    IODeviceTab(QTabWidget *parent = nullptr);
    IODeviceTab(QTabWidget *parent = nullptr, QUdpSocket *udpSocket = nullptr);
    void setUdpSocket(QUdpSocket *value);

private slots:
    void btnClickedRequestInfo();
    void broadcastDatagram(QByteArray data, quint16 port);
    void processPendingDatagrams();

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
    QPlainTextEdit *textEditMsg = nullptr;
    QUdpSocket *udpSocket;
    void createArduinoConfigLayout();
    void createConnectedDevicesLayout();



};
#endif // IODEVICESTAB_H
