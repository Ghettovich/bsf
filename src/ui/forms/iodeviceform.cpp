#include "ui_iodeviceform.h"
#include "iodeviceform.h"
#include <repo/arduinorepo.h>
#include <repo/iodevicerepo.h>
#include <factory/iodeviceformfactory.h>
#include <QVariant>
#include <utility>

IODeviceForm::IODeviceForm(QWidget *parent) :
        QWidget(parent)
        , payloadService(this)
        , ui(new Ui::IODeviceForm)
        , ioDeviceType(0) {
    ui->setupUi(this);

    // LAYOUT
    grid = new QGridLayout(ui->groupBoxConnectedIO);
    grid->setContentsMargins(5, 40, 5, 5);

    // SIGNALS & SLOTS
    // COMBO BOX
    connect(ui->comboBoxIODevices, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onCreateIODeviceTypeFormList(int)));

    //    connect(&payloadService, &PayloadService::onSendIODeviceDtoList,
//                     this, &IODeviceForm::onUpdateIODeviceState);
}

IODeviceForm::~IODeviceForm() {
    delete ui;
}

void IODeviceForm::onCreateArduinoDeviceTypeIOComboBox(QVector<IODeviceType> _ioDeviceTypeList) {
        ioDeviceTypeList = std::move(_ioDeviceTypeList);
        qDebug("(IODeviceForm-->oncreate) io device list size = %s",
               qUtf8Printable(QString::number(ioDeviceTypeList.size())));

        if (!ioDeviceTypeList.empty()) {
            qDebug("io device list NOT empty...");
            ui->comboBoxIODevices->setEnabled(true);
            for (int j = 0; j < ioDeviceTypeList.size(); ++j) {
                QVariant id(ioDeviceTypeList[j].getId());
                qDebug("variant id = %s", qUtf8Printable(qUtf8Printable(QString::number(id.toInt()))));
                qDebug("type = %s", qUtf8Printable(qUtf8Printable(ioDeviceTypeList[j].getType())));
                ui->comboBoxIODevices->addItem(ioDeviceTypeList[j].getType());
                ui->comboBoxIODevices->setItemData(j, id);
            }
        } else {
            qDebug("%s", qUtf8Printable("no io device types"));
            ui->comboBoxIODevices->setEnabled(false);
        }

    qDebug("end method");
}

void IODeviceForm::createWeightSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating weight sensor widget..."));
    int column = 0, row = 0, maxColumnCount = 2;

    for (auto weightSensor: weightSensorList) {
        if (column == maxColumnCount) {
            column = 0;
            row++;
        }
        weightSensor.setIoDeviceType(ioDeviceType);
        auto ioDeviceForm = IODeviceFormFactory::createWeightSensorForm(this, weightSensor);
        grid->addWidget(ioDeviceForm, row, column, Qt::AlignLeft);
        column++;
    }
    //setLayout(grid);
}

void IODeviceForm::createDetectionSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating detection sensor widgets..."));
    int maxColumnCount = 2;
    payloadService.requestStatePayload();
    createIODeviceWidgets(maxColumnCount, IODeviceType::DETECTIONSENSOR);
}

void IODeviceForm::createRelayFormWidgets() {
    qDebug("%s", qUtf8Printable("creating relay widgets..."));
    int maxColumnCount = 2;
    payloadService.requestStatePayload();
    createIODeviceWidgets(maxColumnCount, IODeviceType::RELAY);
}

void IODeviceForm::createIODeviceWidgets(int maxColumnCount, int _ioDeviceType) {
    int column = 0, row = 0;
    IODeviceRepository ioDeviceRepository;
    ioDeviceType = ioDeviceRepository.getIODeviceType(_ioDeviceType);

    for (auto ioDevice: ioDeviceList) {
        if (column == maxColumnCount) {
            column = 0;
            row++;
        }

        ioDevice.setIoDeviceType(ioDeviceType);
        auto ioDeviceForm = IODeviceFormFactory::createIODeviceForm(_ioDeviceType, this, ioDevice);
        grid->addWidget(ioDeviceForm, row, column, Qt::AlignLeft);
        column++;
    }
    ui->groupBoxConnectedIO->setLayout(grid);
    ui->groupBoxConnectedIO->layout()->setSizeConstraint(QLayout::SetMinimumSize);
}

void IODeviceForm::killChildWidgets() {
    while(!grid->isEmpty()) {
        auto widget = grid->takeAt(0)->widget();
        widget->deleteLater();
        qDebug("%s", qUtf8Printable("child deleted"));
    }
}

void IODeviceForm::onCreateIODeviceTypeFormList(int index) {
    killChildWidgets();
    ioDeviceList.clear();
    weightSensorList.clear();
    QVariant id;
    IODeviceRepository ioDeviceRepository;
    int deviceTypeId = ui->comboBoxIODevices->itemData(index).toInt();
    qDebug("device type id = %s", qUtf8Printable(QString::number(deviceTypeId)));

    switch (deviceTypeId) {
        case IODeviceType::WEIGHTSENSOR :
            qDebug("ceating forms for weight sensor cell");
            weightSensorList = ioDeviceRepository.getArduinoWeightSensorList(arduino.getId());
            qDebug("got devices..");
            createWeightSensorWidgets();
            break;
        case IODeviceType::DETECTIONSENSOR :
            qDebug("creating forms for detection sensor");
            ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduino.getId(), IODeviceType::DETECTIONSENSOR);
            qDebug("got devices..");
            createDetectionSensorWidgets();
            break;
        case IODeviceType::RELAY :
            qDebug("creating forms for relay");
            ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduino.getId(), IODeviceType::RELAY);
            qDebug("got devices..");
            createRelayFormWidgets();
            break;
        default:
            qDebug("unknown device type id! id = %s", qUtf8Printable(QString::number(deviceTypeId)));
            break;
    }
}

