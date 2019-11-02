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

    QGroupBox *groupBoxArduino;

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
    QPushButton *btnSaveport;
    QPushButton *btnRecoverDescription;
    QPushButton *btnSaveDescription;

    QPushButton *btnPing;
    QPushButton *btnRequestState;
    QPushButton *btnAuthenticate;

    QPlainTextEdit *plainTextEditDescription;
    QPlainTextEdit plainTextEditResponse;

private:
    Ui::bsfDeviceFormWidget ui;

};