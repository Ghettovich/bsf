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
    explicit RelayForm(QWidget *parent = nullptr, IODevice *_ioDevice = nullptr);
    virtual ~RelayForm();

    void createItems();
    void setButtonState(bool isRelayLow);

    QGroupBox *groupBox = nullptr;
private:
    QLabel *lblRelayDescription = nullptr;;
    QPushButton *btnLow = nullptr;;
    QPushButton *btnHigh = nullptr;;
    QPlainTextEdit *response = nullptr;
    IODevice *ioDevice = nullptr;
    quint16 destPort = 0;

    QUdpSocket *udpSocket = nullptr;
    QHostAddress *bcast = nullptr;
    Ui::RelayForm *ui;

    void onClickBtnLow();
    void onClickBtnHigh();

private slots:
    void readDatagrams();
};
#endif //BSF_RELAYFORM_H