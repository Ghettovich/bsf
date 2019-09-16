#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTimer>
#include <QUdpSocket>
#include <server.h>

class ArduinoTab : public QTabWidget
{
    Q_OBJECT

public:
    explicit ArduinoTab(QTabWidget *parent = nullptr);

private slots:
    void btnClickLED1();

private:
    bool isLED1_ON = false;

    QLabel *lblPingDevice = nullptr;
    QPushButton *btnPingArduino = nullptr;
    QPushButton *btnLED1 = nullptr;
    QPlainTextEdit *textEditMsg = nullptr;

    //Server *udpServer;

    void createButtons();
    void createLabels();
    void createPlainTextFields();
};
#endif // ARDUINOSTAB_H
