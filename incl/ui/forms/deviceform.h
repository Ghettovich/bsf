#include <data/dbmanager.h>
#include "ui_devicewidget.h"

#ifndef BSF_DEVICEFORM_H
#define BSF_DEVICEFORM_H

#endif //BSF_DEVICEFORM_H

class DeviceForm : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceForm(QWidget *parent = nullptr);
    void initWidget(arduino &arduinoDevice);

    QGroupBox *groupBoxArduino;

private:
    Ui::bsfDeviceFormWidget ui;
    arduino arduinoDev;

    QLabel *lblName;
    QLabel *lblIpAddress;
    QLabel *lblPort;
    QLabel *lblDescription;

    QLineEdit *lineEditName;
    QLineEdit *lineEditIpAddress;
    QLineEdit *lineEditNPort;

    QPushButton *btnRecoverName;
    QPushButton *btnSaveName;
    QPushButton *btnRecoverIpAddress;
    QPushButton *btnSaveIpAddress;
    QPushButton *btnRecoverPort;
    QPushButton *btnSavePort;
    QPushButton *btnRecoverDescription;
    QPushButton *btnSaveDescription;

    QPushButton *btnPing;
    QPushButton *btnRequestState;
    QPushButton *btnAuthenticate;

    QPlainTextEdit *plainTextEditDescription;
    QPlainTextEdit plainTextEditResponse;

    void onClickRecoverDescription();
    void onClickSaveDescription();
    void onClickRecoverIpAddress();
    void onClickSaveIpAddress();
    void onClickRecoverName();
    void onClickSaveName();
    void onClickRecoverPort();
    void onClickSavePort();
    void createForm();
    void createTestButtons();
};