#include <QtWidgets/QWidget>
#include "incl/ui/forms/deviceform.h"

DeviceForm::DeviceForm(QWidget *parent) :
        QWidget(parent) {
    ui.setupUi(this);
    createForm();
    createTestButtons();
}

void DeviceForm::createForm() {
    // Init
    groupBoxArduino = ui.groupBoxDevice;
    // Labels
    lblDescription = ui.labelDescription;
    lblIpAddress = ui.labelIpAddress;
    lblName = ui.labelName;
    lblPort = ui.labelPort;
    // Line Edits
    lineEditName = ui.lineEditName;
    lineEditIpAddress = ui.lineEditIPAddress;
    lineEditNPort = ui.lineEditPort;
    // Plain Text Edit
    plainTextEditDescription = ui.plainTextEditDescription;
    // Push Buttons
    btnRecoverDescription = ui.pushButtonRecoverDescription;
    btnSaveDescription = ui.pushButtonSaveDescription;
    btnRecoverIpAddress = ui.pushButtonRecoverIP;
    btnSaveIpAddress = ui.pushButtonSaveIP;
    btnRecoverName = ui.pushButtonRecoverName;
    btnSaveName = ui.pushButtonSaveName;
    btnRecoverPort = ui.pushButtonRecoverPort;
    btnSavePort = ui.pushButtonSavePort;
    // Events
    connect(btnRecoverDescription, &QPushButton::clicked, this, &DeviceForm::onClickRecoverDescription);
    connect(btnSaveDescription, &QPushButton::clicked, this, &DeviceForm::onClickSaveDescription);
    connect(btnRecoverIpAddress, &QPushButton::clicked, this, &DeviceForm::onClickRecoverIpAddress);
    connect(btnSaveIpAddress, &QPushButton::clicked, this, &DeviceForm::onClickSaveIpAddress);
    connect(btnRecoverName, &QPushButton::clicked, this, &DeviceForm::onClickRecoverName);
    connect(btnSaveName, &QPushButton::clicked, this, &DeviceForm::onClickSaveName);
    connect(btnRecoverPort, &QPushButton::clicked, this, &DeviceForm::onClickRecoverPort);
    connect(btnSavePort, &QPushButton::clicked, this, &DeviceForm::onClickSavePort);
}

void DeviceForm::createTestButtons() {
    btnPing = ui.pushButtonPing;
    btnRequestState = ui.pushButtonRequestState;
    btnAuthenticate = ui.pushButtonAuthenticate;
}

void DeviceForm::initWidget(arduino &arduinoDevice) {
    arduinoDev = arduinoDevice;
    groupBoxArduino->setTitle(arduinoDev.name);
    lineEditName->setText(arduinoDev.name);
    lineEditIpAddress->setText(arduinoDev.ipAddress);
    lineEditNPort->setText(QStringLiteral("%1").arg(arduinoDev.port));
    plainTextEditDescription->setPlainText(arduinoDev.desc);
}

void DeviceForm::onClickRecoverDescription() {
    plainTextEditDescription->setPlainText(arduinoDev.desc);
}

void DeviceForm::onClickSaveDescription() {

}

void DeviceForm::onClickRecoverIpAddress() {
    lineEditIpAddress->setText(arduinoDev.ipAddress);
}

void DeviceForm::onClickSaveIpAddress() {

}

void DeviceForm::onClickRecoverName() {
    lineEditName->setText(arduinoDev.name);
}

void DeviceForm::onClickSaveName() {

}

void DeviceForm::onClickRecoverPort() {
    lineEditName->setText(QStringLiteral("%1").arg(arduinoDev.port));
}

void DeviceForm::onClickSavePort() {

}




