#ifndef BSF_RELAYFORM_H
#define BSF_RELAYFORM_H

#include <QtNetwork/QUdpSocket>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QPlainTextEdit>
#include <incl/domain/actionarduino.h>

namespace Ui {
    class RelayForm;
}

class RelayForm : public QWidget {
Q_OBJECT

public:
    explicit RelayForm(QWidget *parent = nullptr);
    virtual ~RelayForm();
    //;
    void createItems();
    void initWidget(ArduinoAction &arduinoAction);

private:
    Ui::RelayForm *ui;
    QGroupBox *groupBox{};
    QLabel *lblRelayDescription{};
    QPushButton *btnLow{};
    QPushButton *btnHigh{};
    QPlainTextEdit *response{};
    ArduinoAction arduinoAction{};
    //RelayRepository relayRepository{};

    quint16 portListenOn = 12300;
    QUdpSocket *udpSocket;

    void defaultButtonState();
    void setButtonState(bool isRelayLow);
    void onClickBtnLow();
    void onClickBtnHigh();

private slots:
    void readDatagrams();
};
#endif //BSF_RELAYFORM_H