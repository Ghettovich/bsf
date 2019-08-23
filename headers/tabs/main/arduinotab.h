#ifndef ARDUINOTAB_H
#define ARDUINOTAB_H

#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QUdpSocket>

class ArduinoTab : public QTabWidget
{
    Q_OBJECT

public:
    explicit ArduinoTab(QTabWidget *parent = nullptr);

private slots:
    void processPendingDatagrams();

private:
    quint16 port = 9900;
    bool isListening = false;

    QLabel *lblPingDevice = nullptr;
    QPushButton *btnPingArduino = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QPlainTextEdit *textEditMsg = nullptr;

    void initSocket();
    void createButtons();
    void createLabels();
    void createPlainTextFields();
};
#endif // ARDUINOSTAB_H
