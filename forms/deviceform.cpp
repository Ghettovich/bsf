#include <QtWidgets/QWidget>
#include "deviceform.h"

DeviceForm::DeviceForm(QWidget *parent) :
        QWidget(parent) {
    ui.setupUi(this);
    createForm();
    createTestButtons();
}


void DeviceForm::createForm() {
    groupBoxArduino = ui.groupBoxDevice;

    lblName = ui.labelName;
    lblIpAddress = ui.labelIpAddress;
    lblPort = ui.labelPort;
    lblDescription = ui.labelDescription;

    lineEditName = ui.lineEditName;
    lineEditIpAddress = ui.lineEditIPAddress;
    lineEditNPort = ui.lineEditPort;

    plainTextEditDescription = ui.plainTextEditDescription;

    btnRecoverName = ui.pushButtonRecoverName;
    btnSaveName = ui.pushButtonSaveName;
    btnRecoverIpAddress = ui.pushButtonRecoverIP;
    btnSaveIpAddress = ui.pushButtonSaveIP;
    btnRecoverPort = ui.pushButtonRecoverPort;
    btnSaveport = ui.pushButtonSavePort;
    btnRecoverDescription = ui.pushButtonRecoverDescription;
    btnSaveDescription = ui.pushButtonSaveDescription;
}

void DeviceForm::createTestButtons() {
    btnPing = ui.pushButtonPing;
    btnRequestState = ui.pushButtonRequestState;
    btnAuthenticate = ui.pushButtonAuthenticate;
}