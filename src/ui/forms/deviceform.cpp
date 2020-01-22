#include "ui_deviceform.h"
#include "deviceform.h"
#include <service/logservice.h>
#include <repo/arduinorepo.h>

DeviceForm::DeviceForm(QWidget *parent, const Qt::WindowFlags &f) :
        QWidget(parent, f)
        , ui(new Ui::DeviceForm) {
    ui->setupUi(this);
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
    ui->groupBoxDevice->setTitle(arduinoDev.getName());
    ui->lineEditName->setText(arduinoDev.getName());
    ui->lineEditIPAddress->setText(arduinoDev.getIpAddress());
    ui->lineEditPort->setText(QStringLiteral("%1").arg(arduinoDev.getPort()));
    ui->plainTextEditDescription->setPlainText(arduinoDev.getDesc());
    // copy back up
    tempArduinoDev.setName(arduinoDevice.getName());
    tempArduinoDev.setPort(arduinoDevice.getPort());
    tempArduinoDev.setIpAddress(arduinoDevice.getIpAddress());
    tempArduinoDev.setDesc(arduinoDevice.getDesc());
}

void DeviceForm::onClickRecoverDescription() {
    ui->plainTextEditDescription->setPlainText(tempArduinoDev.getDesc());
}

void DeviceForm::onClickSaveDescription() {
    tempArduinoDev.setDesc(arduinoDev.getDesc());
    updateArduino();
    BsfLogService logService;
    logService.addLog("changed description of arduino", BafaLog::INFO);
}

void DeviceForm::onClickRecoverIpAddress() {
    ui->lineEditIPAddress->setText(tempArduinoDev.getIpAddress());
}

void DeviceForm::onClickSaveIpAddress() {
    tempArduinoDev.setIpAddress(arduinoDev.getIpAddress());
    updateArduino();
}

void DeviceForm::onClickRecoverName() {
    ui->lineEditName->setText(tempArduinoDev.getName());
}

void DeviceForm::onClickSaveName() {
    updateArduino();
    pal.setColor(QPalette::Base, Qt::white);
    ui->lineEditPort->setPalette(pal);
    tempArduinoDev.setName(arduinoDev.getName());
    ui->groupBoxDevice->setTitle(arduinoDev.getName());
    ui->lineEditName->setText(arduinoDev.getName());
}

void DeviceForm::onClickRecoverPort() {
    ui->lineEditPort->setText(QString::number(arduinoDev.getPort()));
    pal.setColor(QPalette::Base, Qt::white);
    ui->lineEditPort->setPalette(pal);
}

void DeviceForm::onClickSavePort() {
    updateArduino();
    tempArduinoDev.setPort(arduinoDev.getPort());
    pal.setColor(QPalette::Base, Qt::white);
    ui->lineEditPort->setPalette(pal);
}

void DeviceForm::onChangeLineEditName() {
    arduinoDev.setName(ui->lineEditName->text());
}

void DeviceForm::onChangeLineEditIpAddress() {
    arduinoDev.setIpAddress(ui->lineEditIPAddress->text());
}

void DeviceForm::onChangeLineEditPort() {
    if (ui->lineEditPort->isModified()) {
        if (QString(ui->lineEditPort->text()).toInt()) {
            arduinoDev.setPort(QString(ui->lineEditPort->text()).toInt());
            pal.setColor(QPalette::Base, Qt::green);
        } else {
            pal.setColor(QPalette::Base, Qt::red);
        }
        ui->lineEditPort->setPalette(pal);
    }
}

void DeviceForm::onChangePlainTextDescription() {
    arduinoDev.setDesc(ui->plainTextEditDescription->toPlainText());
}

void DeviceForm::updateArduino() {
    ArduinoRepository arduinoRepository;
    arduinoRepository.updateArduino(arduinoDev);
}
