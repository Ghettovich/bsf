#ifndef BSF_RELAYFORM_H
#define BSF_RELAYFORM_H

#include <domain/relay.h>
#include <service/payloadservice.h>
#include <QUrl>
#include <QtWidgets/QWidget>

namespace Ui {
    class RelayForm;
}

class RelayForm : public QWidget {

    Q_OBJECT

public:
    RelayForm(QWidget *parent, const Qt::WindowFlags &f, Relay&);

    virtual ~RelayForm();
    void createItems();
    void requestState();

public slots:
    void setIODeviceState(IODevice::IO_DEVICE_HIGH_LOW);

signals:
    void sendRequest(QUrl&);

private:
    Relay relay;
    Ui::RelayForm *ui;

    void onClickBtnLow();
    void onClickBtnHigh();

};
#endif //BSF_RELAYFORM_H