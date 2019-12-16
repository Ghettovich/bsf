#include "ui_iodeviceform.h"
#include "incl/ui/forms/iodeviceform.h"
#include <incl/factory/iodeviceformfactory.h>

IODeviceForm::IODeviceForm(QWidget *_parent, Arduino *_arduino) :
        QWidget(_parent), ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    arduino = _arduino;

    //SERVICE
    payloadService = new PayloadService(this);

    // DATA
    stateCodeRepository = new StateCodeRepository;
    ioDeviceRepository = new IODeviceRepository;
    createArduinoDeviceTypeIOComboBox();

    // LAYOUT
    grid = new QGridLayout(ui->groupBoxConnectedIO);
    grid->setContentsMargins(5, 40, 5, 5);
    // CREATE widgets with first item in Combo Box
    createIODeviceTypeFormList(ui->comboBoxIODevices->itemText(0));

    // SIGNALS & SLOTS
    // COMBO BOX
    connect(ui->comboBoxIODevices, SIGNAL(currentIndexChanged(
                                                  const QString&)), this, SLOT(createIODeviceTypeFormList(
                                                                                       const QString&)));

    QObject::connect(payloadService, &PayloadService::onSendIODeviceDtoList,
                     this, &IODeviceForm::onUpdateIODeviceState);
}

IODeviceForm::~IODeviceForm() {
    delete ui;
}

void IODeviceForm::createArduinoDeviceTypeIOComboBox() {
    ioDeviceTypeList = ioDeviceRepository->getArduinoIODeviceTypes(arduino->id);

    if(!ioDeviceTypeList.empty()) {
        ui->comboBoxIODevices->setEnabled(true);
        qDebug("got id: %s", qUtf8Printable(QString::number(arduino->id)));
        for (auto &_ioDeviceType: ioDeviceTypeList) {
            ui->comboBoxIODevices->addItem(_ioDeviceType.type, _ioDeviceType.id);
        }
    } else {
        qDebug("%s", qUtf8Printable("no io device types"));
        ui->comboBoxIODevices->setEnabled(false);
    }

}

void IODeviceForm::updateArduinoDeviceTypeIOComboBox(Arduino &_arduino) {
    ui->comboBoxIODevices->clear();
    ioDeviceTypeList.clear();
    arduino = &_arduino;
    createArduinoDeviceTypeIOComboBox();
}

void IODeviceForm::createWeightSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating weight sensor widget..."));
    int maxColumnCount = 2;
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::WEIGHTSENSOR);
}

void IODeviceForm::createDetectionSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating detection sensor widgets..."));
    int maxColumnCount = 2;
    payloadService->requestStatePayload();
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::DETECTIONSENSOR);
}

void IODeviceForm::createRelayFormWidgets() {
    qDebug("%s", qUtf8Printable("creating relay widgets..."));
    int maxColumnCount = 2;
    payloadService->requestStatePayload();
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::RELAY);
}

void IODeviceForm::createIODeviceWidgets(int maxColumnCount, int _ioDeviceType) {
    int column = 0, row = 0;
    ioDeviceType = ioDeviceRepository->getIODeviceType(_ioDeviceType);

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
void IODeviceForm::createIODeviceTypeFormList(const QString &deviceType) {
    killChildWidgets();
    ioDeviceList.clear();
    ioDeviceFormList.clear();

    if (QString::compare(deviceType, "weightsensor") == 0) {
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::WEIGHTSENSOR);
        createWeightSensorWidgets();
    } else if (QString::compare(deviceType, "detectionsensor") == 0) {
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::DETECTIONSENSOR);
        createDetectionSensorWidgets();
    } else if (QString::compare(deviceType, "relay") == 0) {
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::RELAY);
        createRelayFormWidgets();
    } else {
        qDebug("%s", qUtf8Printable("Could not find matching device type"));
    }
}

void IODeviceForm::onUpdateIODeviceState(const QList<IODeviceDTO *>& dtoList) {
    // Disgusting, but functional
    for(auto dev : ioDeviceList) {
        for(auto dto : dtoList) {
            if(dev->getId() == dto->id) {
                qInfo() << "Found id to update in io device form";
                emit dev->deviceStateValueChanged(dto->low == 1 ? IODeviceState::LOW : IODeviceState::HIGH);
            }
        }
    }
}
