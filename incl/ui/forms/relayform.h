#ifndef BSF_RELAYFORM_H
#define BSF_RELAYFORM_H

#include <QtNetwork/QUdpSocket>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QPlainTextEdit>
#include <incl/domain/iodevice.h>

namespace Ui {
    class RelayForm;
}

class RelayForm : public QWidget {
Q_OBJECT

public:
    explicit RelayForm(QWidget *parent = nullptr);
    virtual ~RelayForm();

    void createItems();
    void initWidget(const IODevice &_ioDevice);
    void setButtonState(bool isRelayLow);

private:
    QGroupBox *groupBox = nullptr;
    QLabel *lblRelayDescription = nullptr;;
    QPushButton *btnLow = nullptr;;
    QPushButton *btnHigh = nullptr;;
    QPlainTextEdit *response = nullptr;
    IODevice ioDevice;
    quint16 portListenOn = 12300;

    QUdpSocket *udpSocket;
    Ui::RelayForm *ui;

    void defaultButtonState();
    void onClickBtnLow();
    void onClickBtnHigh();

private slots:
    void readDatagrams();
};
#endif //BSF_RELAYFORM_H