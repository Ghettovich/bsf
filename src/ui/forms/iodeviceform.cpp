#include "ui_iodeviceform.h"
#include "iodeviceform.h"
#include "deviceactionform.h"
#include <factory/iodeviceformfactory.h>

IODeviceForm::IODeviceForm(QWidget *_parent) :
        QWidget(_parent), ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    //arduino = _arduino;

    //SERVICE
    //payloadService = new PayloadService();

    // DATA
    //ioDeviceRepository = new IODeviceRepository;
    onCreateArduinoDeviceTypeIOComboBox(0);

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

void IODeviceForm::onCreateArduinoDeviceTypeIOComboBox(int arduinoId) {
    IODeviceRepository ioDeviceRepository;
    ioDeviceTypeList = ioDeviceRepository.getArduinoIODeviceTypes(arduinoId);

    if(!ioDeviceTypeList.empty()) {
        ui->comboBoxIODevices->setEnabled(true);
        for (auto &_ioDeviceType: ioDeviceTypeList) {
            ui->comboBoxIODevices->addItem(_ioDeviceType.type, _ioDeviceType.id);
        }
    } else {
        qDebug("%s", qUtf8Printable("no io device types"));
        ui->comboBoxIODevices->setEnabled(false);
    }
}

void IODeviceForm::createWeightSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating weight sensor widget..."));
    int maxColumnCount = 2;
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::WEIGHTSENSOR);
}

void IODeviceForm::createDetectionSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating detection sensor widgets..."));
    int maxColumnCount = 2;
    payloadService.requestStatePayload();
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::DETECTIONSENSOR);
}

void IODeviceForm::createRelayFormWidgets() {
    qDebug("%s", qUtf8Printable("creating relay widgets..."));
    int maxColumnCount = 2;
    payloadService.requestStatePayload();
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::RELAY);
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
        ioDevice->setIoDeviceType(*ioDeviceType);
        auto *ioDeviceForm = IODeviceFormFactory::getIODeviceForm(_ioDeviceType, this, ioDevice);
        ioDeviceFormList.append(ioDeviceForm);
        grid->addWidget(ioDeviceForm, row, column, Qt::AlignLeft);
        column++;
    }
    ui->groupBoxConnectedIO->setLayout(grid);
    ui->groupBoxConnectedIO->layout()->setSizeConstraint(QLayout::SetMinimumSize);
}

void IODeviceForm::killChildWidgets() {
    for (auto *form: ioDeviceFormList) {
        form->deleteLater();
        qDebug("%s", qUtf8Printable("child deleted"));
    }
}

/* PRIVATE SLOTS */
void IODeviceForm::onCreateIODeviceTypeFormList(int ioDeviceTypeId) {
    killChildWidgets();
    ioDeviceList.clear();
    ioDeviceFormList.clear();

    IODeviceRepository ioDeviceRepository;


    switch(ioDeviceTypeId) {
        case WEIGHTSENSOR :
            ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::WEIGHTSENSOR);
            createWeightSensorWidgets();
            break;
        case DETECTIONSENSOR :
            ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::DETECTIONSENSOR);
            createDetectionSensorWidgets();
            break;
        case RELAY :
            ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::RELAY);
            createRelayFormWidgets();
            break;
        default:
            qDebug("unknown device type id! id = %s", qUtf8Printable(QString::number(ioDeviceTypeId)));
            break;
    }

//    if (QString::compare(deviceType, "weightsensor") == 0) {
//        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::WEIGHTSENSOR);
//        createWeightSensorWidgets();
//    } else if (QString::compare(deviceType, "detectionsensor") == 0) {
//        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::DETECTIONSENSOR);
//    } else if (QString::compare(deviceType, "relay") == 0) {
//        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::RELAY);
//        createRelayFormWidgets();
//    } else {
//        qDebug("%s", qUtf8Printable("Could not find matching device type"));
//    }
}

//void IODeviceForm::onUpdateIODeviceState(const QList<IODeviceDTO *>& dtoList) {
//    // Disgusting, but functional
//    qInfo() << "onUpdateIODeviceState in io device form called 1243124asd";
//    for(auto dev : ioDeviceList) {
//        for(auto dto : dtoList) {
//            if(dev->getId() == dto->id) {
//                qInfo() << "Found id to update in io device form";
//                emit dev->deviceStateValueChanged(dto->low == 1 ? IODeviceState::LOW : IODeviceState::HIGH);
//            }
//        }
//    }
//}
