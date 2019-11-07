#include <QtWidgets/QWidget>
#include "incl/ui/forms/deviceform.h"
#include <QtGlobal>
#include <utility>

DeviceForm::DeviceForm(DeviceController deviceManager, QWidget *parent) :
        deviceManager(std::move(deviceManager)),
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
    lineEditPort = ui.lineEditPort;
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
    // Plain Text Events
    connect(plainTextEditDescription, &QPlainTextEdit::textChanged, this, &DeviceForm::onChangePlainTextDescription);
    // Line Edit Events
    connect(lineEditIpAddress, &QLineEdit::textChanged, this, &DeviceForm::onChangeLineEditIpAddress);
    connect(lineEditName, &QLineEdit::textChanged, this, &DeviceForm::onChangeLineEditName);
    connect(lineEditPort, &QLineEdit::textChanged, this, &DeviceForm::onChangeLineEditPort);
    // Button Events
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
    lineEditPort->setText(QStringLiteral("%1").arg(arduinoDev.port));
    plainTextEditDescription->setPlainText(arduinoDev.desc);
    // copy back up
    tempArduinoDev.name = arduinoDevice.name;
    tempArduinoDev.port = arduinoDevice.port;
    tempArduinoDev.ipAddress = arduinoDevice.ipAddress;
    tempArduinoDev.desc = arduinoDevice.desc;
    tempArduinoDev.id = arduinoDevice.id;
}

void DeviceForm::onClickRecoverDescription() {
    plainTextEditDescription->setPlainText(tempArduinoDev.desc);
}

void DeviceForm::onClickSaveDescription() {
    qDebug("temp desc: %s", qUtf8Printable(tempArduinoDev.desc));
    deviceManager.updateArduinoDevice(arduinoDev);
}

void DeviceForm::onClickRecoverIpAddress() {
    lineEditIpAddress->setText(tempArduinoDev.ipAddress);
}

void DeviceForm::onClickSaveIpAddress() {
    deviceManager.updateArduinoDevice(arduinoDev);
}

void DeviceForm::onClickRecoverName() {
    lineEditName->setText(tempArduinoDev.name);
}

void DeviceForm::onClickSaveName() {
    deviceManager.updateArduinoDevice(arduinoDev);
    pal.setColor(QPalette::Base, Qt::white);
    lineEditPort->setPalette(pal);
}

void DeviceForm::onClickRecoverPort() {
    lineEditPort->setText(QStringLiteral("%1").arg(tempArduinoDev.port));
    pal.setColor(QPalette::Base, Qt::white);
    lineEditPort->setPalette(pal);
}

void DeviceForm::onClickSavePort() {
    deviceManager.updateArduinoDevice(arduinoDev);
    pal.setColor(QPalette::Base, Qt::white);
    lineEditPort->setPalette(pal);
}

void DeviceForm::onChangeLineEditName() {
    arduinoDev.name = lineEditName->text();
    qDebug("line %s", qUtf8Printable(lineEditName->text()));
}

void DeviceForm::onChangeLineEditIpAddress() {
    arduinoDev.ipAddress = lineEditIpAddress->text();
}

void DeviceForm::onChangeLineEditPort() {
    if (lineEditPort->isModified()) {
        if (QString(lineEditPort->text()).toInt()) {
            arduinoDev.port = QString(lineEditPort->text()).toInt();
            pal.setColor(QPalette::Base, Qt::green);
        } else {
            pal.setColor(QPalette::Base, Qt::red);
        }
        lineEditPort->setPalette(pal);
    }
}

void DeviceForm::onChangePlainTextDescription() {
    arduinoDev.desc = plainTextEditDescription->toPlainText();
}
