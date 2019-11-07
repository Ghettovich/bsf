#ifndef BSF_DEVICEFORM_H
#define BSF_DEVICEFORM_H

#include "ui_devicewidget.h"
#include "devicecontroller.h"

class DeviceForm : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceForm(DeviceController deviceManager, QWidget *parent = nullptr);
    void initWidget(arduino &arduinoDevice);

public slots:
    void onChangeLineEditIpAddress();
    void onChangeLineEditName();
    void onChangeLineEditPort();
    void onChangePlainTextDescription();

private:
    Ui::bsfDeviceFormWidget ui{};
    arduino arduinoDev;
    arduino tempArduinoDev;
    DeviceController deviceManager;

    QGroupBox *groupBoxArduino{};

    QLabel *lblName{};
    QLabel *lblIpAddress{};
    QLabel *lblPort{};
    QLabel *lblDescription{};

    QLineEdit *lineEditName{};
    QLineEdit *lineEditIpAddress{};
    QLineEdit *lineEditPort{};

    QPushButton *btnRecoverName{};
    QPushButton *btnSaveName{};
    QPushButton *btnRecoverIpAddress{};
    QPushButton *btnSaveIpAddress{};
    QPushButton *btnRecoverPort{};
    QPushButton *btnSavePort{};
    QPushButton *btnRecoverDescription{};
    QPushButton *btnSaveDescription{};

    QPushButton *btnPing{};
    QPushButton *btnRequestState{};
    QPushButton *btnAuthenticate{};

    QPlainTextEdit *plainTextEditDescription{};
    QPlainTextEdit *plainTextEditResponse{};
    QPalette pal;

    void createForm();
    void createTestButtons();
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