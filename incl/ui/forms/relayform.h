#ifndef BSF_RELAYFORM_H
#define BSF_RELAYFORM_H

#include <QtNetwork/QUdpSocket>
#include <QtWidgets/QWidget>
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

public slots:
    void setButtonState(bool isRelayLow);
    void setRelayButtonState(QChar isLow);

private:
    IODevice *ioDevice = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QHostAddress *bcast = nullptr;
    Ui::RelayForm *ui;

    void onClickBtnLow();
    void onClickBtnHigh();

private slots:
    void readDatagrams();
};
#endif //BSF_RELAYFORM_H