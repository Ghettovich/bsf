#ifndef BSF_DEVICEFORM_H
#define BSF_DEVICEFORM_H

#include <incl/domain/log.h>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <incl/domain/arduino.h>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QPlainTextEdit>
#include <incl/repo/arduinorepo.h>

namespace Ui {
    class DeviceForm;
}

class DeviceForm : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceForm(QWidget *parent = nullptr);
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
    //DeviceController deviceManager;
    BsfLog log;
    ArduinoRepository *arduinoRepository = new ArduinoRepository;

    QGroupBox *groupBoxArduino = nullptr;
    QLabel *lblName = nullptr;
    QLabel *lblIpAddress = nullptr;
    QLabel *lblPort = nullptr;

    QLabel *lblDescription = nullptr;
    QLineEdit *lineEditName = nullptr;
    QLineEdit *lineEditIpAddress = nullptr;

    QLineEdit *lineEditPort = nullptr;
    QPushButton *btnRecoverName = nullptr;
    QPushButton *btnSaveName = nullptr;
    QPushButton *btnRecoverIpAddress = nullptr;
    QPushButton *btnSaveIpAddress = nullptr;
    QPushButton *btnRecoverPort = nullptr;
    QPushButton *btnSavePort = nullptr;
    QPushButton *btnRecoverDescription = nullptr;

    QPushButton *btnSaveDescription= nullptr;
    QPushButton *btnPing = nullptr;
    QPushButton *btnRequestState = nullptr;

    QPushButton *btnAuthenticate = nullptr;
    QPlainTextEdit *plainTextEditDescription = nullptr;
    QPlainTextEdit *plainTextEditResponse = nullptr;

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
    void createBsfLog(QString logMessage);
};
#endif //BSF_DEVICEFORM_H