#ifndef BSF_RELAYFORM_H
#define BSF_RELAYFORM_H

#include <QtWidgets/QWidget>
#include <service/payloadservice.h>

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
    //void setButtonState();
    void setIODeviceState(IODeviceState state);

private:
    IODevice *ioDevice = nullptr;
    PayloadService *payloadService = nullptr;
    Ui::RelayForm *ui;

    void onClickBtnLow();
    void onClickBtnHigh();

};
#endif //BSF_RELAYFORM_H