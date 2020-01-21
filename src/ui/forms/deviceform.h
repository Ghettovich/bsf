#ifndef BSF_DEVICEFORM_H
#define BSF_DEVICEFORM_H

#include <domain/arduino.h>
#include <QtWidgets/QWidget>

namespace Ui {
    class DeviceForm;
}

class DeviceForm : public QWidget
{
    Q_OBJECT
public:
    DeviceForm(QWidget *parent = nullptr);
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
    void updateArduino();
};
#endif //BSF_DEVICEFORM_H