#ifndef BSF_RELAYFORM_H
#define BSF_RELAYFORM_H

#include <QtNetwork/QUdpSocket>
#include "incl/controller/relaycontroller.h"
#include "incl/repo/arduinorepo.h"
#include "ui_testrelaywidget.h"

class RelayForm : public QWidget {
Q_OBJECT

public:
    explicit RelayForm(RelayController relayController, QWidget *parent = nullptr);
    void createItems();
    void initWidget(ArduinoAction &arduinoAction);

private:
    Ui::bsfTestRelayWidget ui{};
    QLabel *lblRelayDescription{};
    QPushButton *btnLow{};
    QPushButton *btnHigh{};
    QPlainTextEdit *response{};
    RelayController relayController;
    ArduinoAction arduinoAction;

    quint16 portListenOn = 12300;
    QUdpSocket *udpSocket;

    void defaultButtonState();
    void onClickBtnLow();
    void onClickBtnHigh();

private slots:
    void readDatagrams();
};
#endif //BSF_RELAYFORM_H