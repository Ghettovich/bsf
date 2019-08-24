#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTimer>
#include <QUdpSocket>

class ArduinoTab : public QTabWidget
{
    Q_OBJECT

public:
    explicit ArduinoTab(QTabWidget *parent = nullptr);

private slots:
    void processPendingDatagrams();
    void startBroadcasting();
    void broadcastDatagram();
    void btnClickLED1();
    //void btnClickLED2();
    //void btnClickLED3();

private:
    quint16 port = 9900;
    int msgNr = 1;
    bool isListening = false;
    bool isLED1_ON = false;

    QLabel *lblPingDevice = nullptr;
    QPushButton *btnPingArduino = nullptr;
    QPushButton *btnLED1 = nullptr;
    QPushButton *btnLED2 = nullptr;
    QPushButton *btnLED3 = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QPlainTextEdit *textEditMsg = nullptr;
    QTimer timer;

    void initSocket();    
    void createButtons();
    void createLabels();
    void createPlainTextFields();
};
#endif // ARDUINOSTAB_H
