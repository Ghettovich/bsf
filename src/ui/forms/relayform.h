#ifndef BSF_RELAYFORM_H
#define BSF_RELAYFORM_H

#include <domain/iodevice.h>
#include <service/payloadservice.h>
#include <QtWidgets/QWidget>

namespace Ui {
    class RelayForm;
}

class RelayForm : public QWidget {

    Q_OBJECT

public:
    RelayForm(QWidget *parent, const Qt::WindowFlags &f, const IODevice &ioDevice);

    //explicit RelayForm(QWidget *parent, IODevice);
    virtual ~RelayForm();
    void createItems();

public slots:
    void setIODeviceState(int state);

signals:
    void sendRequest(QUrl&);

private:
    IODevice ioDevice;
    Ui::RelayForm *ui;

    void onClickBtnLow();
    void onClickBtnHigh();

};
#endif //BSF_RELAYFORM_H