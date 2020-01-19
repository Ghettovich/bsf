#include "ui_deviceform.h"
#include "deviceform.h"
#include <service/logservice.h>

DeviceForm::DeviceForm(QWidget *parent) :
        QWidget(parent)
        , ui(new Ui::DeviceForm) {
    ui->setupUi(this);
    arduinoRepository = new ArduinoRepository;
    connectSlots();
}

DeviceForm::~DeviceForm() {
    qDebug("deleted device form");
    delete ui;
}

void DeviceForm::connectSlots() {
    // Plain Text Events
    connect(ui->plainTextEditDescription, &QPlainTextEdit::textChanged, this, &DeviceForm::onChangePlainTextDescription);
    // Line Edit Events
    connect(ui->lineEditIPAddress, &QLineEdit::textChanged, this, &DeviceForm::onChangeLineEditIpAddress);
    connect(ui->lineEditName, &QLineEdit::textChanged, this, &DeviceForm::onChangeLineEditName);
    connect(ui->lineEditPort, &QLineEdit::textChanged, this, &DeviceForm::onChangeLineEditPort);
    // Button Events
    connect(ui->pushButtonRecoverDescription, &QPushButton::clicked, this, &DeviceForm::onClickRecoverDescription);
    connect(ui->pushButtonSaveDescription, &QPushButton::clicked, this, &DeviceForm::onClickSaveDescription);
    connect(ui->pushButtonRecoverIP, &QPushButton::clicked, this, &DeviceForm::onClickRecoverIpAddress);
    connect(ui->pushButtonSaveIP, &QPushButton::clicked, this, &DeviceForm::onClickSaveIpAddress);
    connect(ui->pushButtonRecoverName, &QPushButton::clicked, this, &DeviceForm::onClickRecoverName);
    connect(ui->pushButtonSaveName, &QPushButton::clicked, this, &DeviceForm::onClickSaveName);
    connect(ui->pushButtonRecoverPort, &QPushButton::clicked, this, &DeviceForm::onClickRecoverPort);
    connect(ui->pushButtonSavePort, &QPushButton::clicked, this, &DeviceForm::onClickSavePort);
}

void DeviceForm::initWidget(Arduino &arduinoDevice) {
    arduinoDev = arduinoDevice;
    ui->groupBoxDevice->setTitle(arduinoDev.name);
    ui->lineEditName->setText(arduinoDev.name);
    ui->lineEditIPAddress->setText(arduinoDev.ipAddress);
    ui->lineEditPort->setText(QStringLiteral("%1").arg(arduinoDev.port));
    ui->plainTextEditDescription->setPlainText(arduinoDev.desc);
    // copy back up
    tempArduinoDev.name = arduinoDevice.name;
    tempArduinoDev.port = arduinoDevice.port;
    tempArduinoDev.ipAddress = arduinoDevice.ipAddress;
    tempArduinoDev.desc = arduinoDevice.desc;
    tempArduinoDev.id = arduinoDevice.id;
}

void DeviceForm::onClickRecoverDescription() {
    ui->plainTextEditDescription->setPlainText(tempArduinoDev.desc);
}

void DeviceForm::onClickSaveDescription() {
    arduinoRepository->updateArduino(arduinoDev);
    tempArduinoDev.desc = arduinoDev.desc;
}

void DeviceForm::onClickRecoverIpAddress() {
    ui->lineEditIPAddress->setText(tempArduinoDev.ipAddress);
}

void DeviceForm::onClickSaveIpAddress() {
    arduinoRepository->updateArduino(arduinoDev);
    tempArduinoDev.ipAddress = arduinoDev.ipAddress;
    BsfLogService::addLog("changed IP of arduino", LogSeverity::INFO);
}

void DeviceForm::onClickRecoverName() {
    ui->lineEditName->setText(tempArduinoDev.name);
}

void DeviceForm::onClickSaveName() {
    arduinoRepository->updateArduino(arduinoDev);
    pal.setColor(QPalette::Base, Qt::white);
    ui->lineEditPort->setPalette(pal);
    tempArduinoDev.name = arduinoDev.name;
    ui->groupBoxDevice->setTitle(arduinoDev.name);
    ui->lineEditName->setText(arduinoDev.name);
}

void DeviceForm::onClickRecoverPort() {
    ui->lineEditPort->setText(QString::number(arduinoDev.port));
    pal.setColor(QPalette::Base, Qt::white);
    ui->lineEditPort->setPalette(pal);
}

void DeviceForm::onClickSavePort() {
    arduinoRepository->updateArduino(arduinoDev);
    tempArduinoDev.port = arduinoDev.port;
    pal.setColor(QPalette::Base, Qt::white);
    ui->lineEditPort->setPalette(pal);
}

void DeviceForm::onChangeLineEditName() {
    arduinoDev.name = ui->lineEditName->text();
}

void DeviceForm::onChangeLineEditIpAddress() {
    arduinoDev.ipAddress = ui->lineEditIPAddress->text();
}

void DeviceForm::onChangeLineEditPort() {
    if (ui->lineEditPort->isModified()) {
        if (QString(ui->lineEditPort->text()).toInt()) {
            arduinoDev.port = QString(ui->lineEditPort->text()).toInt();
            pal.setColor(QPalette::Base, Qt::green);
        } else {
            pal.setColor(QPalette::Base, Qt::red);
        }
        ui->lineEditPort->setPalette(pal);
    }
}

void DeviceForm::onChangePlainTextDescription() {
    arduinoDev.desc = ui->plainTextEditDescription->toPlainText();
}

