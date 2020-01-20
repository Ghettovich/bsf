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
    explicit RelayForm(IODevice *_ioDevice = nullptr);
    virtual ~RelayForm();
    void createItems();

public slots:
    void setIODeviceState(int state);

private:
    IODevice *ioDevice = nullptr;
    PayloadService *payloadService = nullptr;
    Ui::RelayForm *ui;

    void onClickBtnLow();
    void onClickBtnHigh();

};
#endif //BSF_RELAYFORM_H