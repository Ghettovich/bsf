#include "ui_iodeviceform.h"
#include "iodeviceform.h"
#include "detectionsensorform.h"
#include <repo/arduinorepo.h>
#include <repo/iodevicerepo.h>
#include <factory/iodeviceformfactory.h>
#include <QVariant>
#include <utility>

IODeviceForm::IODeviceForm(QWidget *parent, const Qt::WindowFlags &f) :
        QWidget(parent, f)
        , payloadService(this)
        , networkService(this)
        , selectedIODeviceType(0)
        , ui(new Ui::IODeviceForm) {
    ui->setupUi(this);

    vbox = new QVBoxLayout(this);
    vbox->addWidget(ui->comboBoxIODevices, 0, Qt::AlignLeft);
    vbox->addWidget(ui->groupBoxConnectedIO);

    // LAYOUT
    grid = new QGridLayout(ui->groupBoxConnectedIO);
    //grid->setContentsMargins(10, 50, 10, 10);

    // SIGNALS & SLOTS
    // COMBO BOX
    connect(ui->comboBoxIODevices, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onCreateIODeviceTypeFormList(int)));

    QObject::connect(&networkService, &NetworkService::sendIODeviceListWithNewStates,
            this, &IODeviceForm::onUpdateWithNewStateIODevice);
}

IODeviceForm::~IODeviceForm() {
    delete ui;
}

void IODeviceForm::onCreateArduinoDeviceTypeIOComboBox(Arduino& _arduino, QVector<IODeviceType> _ioDeviceTypeList) {
    arduino = _arduino;
    if(!ioDeviceTypeList.empty())
        ioDeviceList.clear();
    ioDeviceTypeList = std::move(_ioDeviceTypeList);
    qDebug("(IODeviceForm-->oncreate) io device list size = %s",
           qUtf8Printable(QString::number(ioDeviceTypeList.size())));

    if (!ioDeviceTypeList.empty()) {
        ui->comboBoxIODevices->clear();
        selectedIODeviceType = ioDeviceTypeList.first();
        qDebug("io device list NOT empty...");
        ui->comboBoxIODevices->setEnabled(true);
        for (auto & j : ioDeviceTypeList) {
            QVariant id(j.getId());
            qDebug("type = %s", qUtf8Printable(qUtf8Printable(j.getType())));
            ui->comboBoxIODevices->addItem(j.getType());
        }
    } else {
        qDebug("%s", qUtf8Printable("no io device types"));
        ui->comboBoxIODevices->setEnabled(false);
    }

    qDebug("end method");
}

void IODeviceForm::createWeightSensorWidgets() {
    qDebug("ceating forms for weight sensor cell");
    int column = 0, row = 0, maxColumnCount = 2;
    //auto grid = new QGridLayout;
    IODeviceRepository ioDeviceRepository;
    weightSensorList = ioDeviceRepository.getArduinoWeightSensorList(arduino.getId());

    for (auto weightSensor: weightSensorList) {
        if (column == maxColumnCount) {
            column = 0;
            row++;
        }
        weightSensor.setIoDeviceType(selectedIODeviceType);
        WeightSensorForm *weightSensorForm = IODeviceFormFactory::createWeightSensorForm(this, weightSensor);

        grid->addWidget(weightSensorForm, row, column, Qt::AlignLeft);
        column++;
    }
    ui->groupBoxConnectedIO->layout()->setSizeConstraint(QLayout::SetMinimumSize);
}

void IODeviceForm::createDetectionSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating detection sensor widgets..."));
    int column = 0, row = 0, maxColumnCount = 2;
    IODeviceRepository ioDeviceRepository;
    ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduino.getId(),
                                                             selectedIODeviceType.getId());
    for (auto ioDevice: ioDeviceList) {
        if (column == maxColumnCount) {
            column = 0;
            row++;
        }

        // ???
        ioDevice.setIoDeviceType(selectedIODeviceType);
        DetectionSensorForm *detectionSensorForm = IODeviceFormFactory::createDetectionSensorForm(this,ioDevice);
        grid->addWidget(detectionSensorForm, row, column, Qt::AlignLeft);
        column++;

    }
    ui->groupBoxConnectedIO->layout()->setSizeConstraint(QLayout::SetMinimumSize);
}

void IODeviceForm::createRelayFormWidgets() {
    qDebug("%s", qUtf8Printable("creating relay widgets..."));
    int column = 0, row = 0, maxColumnCount = 3;

    IODeviceRepository ioDeviceRepository;
    ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduino.getId(),
                                                             selectedIODeviceType.getId());

    for (auto ioDevice: ioDeviceList) {
        if (column == maxColumnCount) {
            column = 0;
            row++;
        }

        // ???
        ioDevice.setIoDeviceType(selectedIODeviceType);
        RelayForm * relayForm = IODeviceFormFactory::createRelayForm(this, ioDevice);
        QObject::connect(relayForm, &RelayForm::sendRequest, this, &IODeviceForm::onSendRequest);

        grid->addWidget(relayForm, row, column, Qt::AlignLeft);
        column++;
    }
    ui->groupBoxConnectedIO->layout()->setSizeConstraint(QLayout::SetMinimumSize);
}


void IODeviceForm::killChildWidgets() {
    while(!grid->isEmpty()) {
        auto widget = grid->takeAt(0)->widget();
        widget->deleteLater();
        qDebug("%s", qUtf8Printable("child deleted in ioDeviceForm"));
    }
}

void IODeviceForm::onCreateIODeviceTypeFormList(int index) {
    if(index >= 0) {
        killChildWidgets();
        ioDeviceList.clear();
        weightSensorList.clear();
        qDebug("GOT INDEX = %s", qUtf8Printable(QString::number(index)));
        selectedIODeviceType = ioDeviceTypeList[index];

        int deviceTypeId = ui->comboBoxIODevices->itemData(index).toInt();
        QVariant id = ui->comboBoxIODevices->currentData(Qt::UserRole);
        qDebug("device type id = %s", qUtf8Printable(QString::number(deviceTypeId)));
        qDebug("(QVariant)device type id = %s", qUtf8Printable(id.toString()));

        switch (selectedIODeviceType.getIODeviceType()) {
            case IODeviceType::WEIGHTSENSOR :
                createWeightSensorWidgets();
                break;
            case IODeviceType::DETECTIONSENSOR :
                createDetectionSensorWidgets();
                break;
            case IODeviceType::RELAY :
                createRelayFormWidgets();
                break;
            default:
                qDebug("unknown device type id! id = %s",
                       qUtf8Printable(QString::number(selectedIODeviceType.getId())));
                break;
        }
    }
}
void IODeviceForm::onSendRequest(const QUrl &url) {
    networkService.requestPayload(url);
    qDebug() << "Url = " << url.toString();
}
void IODeviceForm::onUpdateWithNewStateIODevice(QVector<IODevice>) {
    qDebug("got new list...");
}

