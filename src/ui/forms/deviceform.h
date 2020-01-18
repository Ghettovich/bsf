#ifndef BSF_DEVICEFORM_H
#define BSF_DEVICEFORM_H

#include <QtWidgets/QWidget>
#include <domain/arduino.h>
#include <repo/arduinorepo.h>

namespace Ui {
    class DeviceForm;
}

class DeviceForm : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceForm(QWidget *parent);
    virtual ~DeviceForm();
    void initWidget(Arduino &arduinoDevice);

public slots:
    void onChangeLineEditIpAddress();
    void onChangeLineEditName();
    void onChangeLineEditPort();
    void onChangePlainTextDescription();

private:
    Ui::DeviceForm *ui;
    Arduino arduinoDev;
    Arduino tempArduinoDev;
    ArduinoRepository *arduinoRepository;

    QPalette pal;
    void connectSlots();
    void onClickRecoverDescription();
    void onClickSaveDescription();
    void onClickRecoverIpAddress();
    void onClickSaveIpAddress();
    void onClickRecoverName();
    void onClickSaveName();
    void onClickRecoverPort();
    void onClickSavePort();
};
#endif //BSF_DEVICEFORM_H