#include <ui_iodeviceform.h>
#include <incl/factory/iodeviceformfactory.h>
#include <incl/ui/forms/iodeviceform.h>

IODeviceForm::IODeviceForm(QWidget *_parent, Arduino *_arduino) :
        QWidget(_parent), ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    parent = _parent;
    arduino = _arduino;

    // DATA
    ioDeviceRepository = new IODeviceRepository;
    createArduinoDeviceTypeIOComboBox();

    // LAYOUT
    grid = new QGridLayout(ui->scrollAreaWidgetContentsIODevices);
    grid->setContentsMargins(20, 60, 10, 10);
    setLayout(grid);

    // SIGNALS & SLOTS
    connect(ui->comboBoxIODevices, SIGNAL(currentIndexChanged(
                                                  const QString&)), this, SLOT(createIODeviceTypeFormList(
                                                                                       const QString&)));
}

IODeviceForm::~IODeviceForm() {
    delete ui;
}

void IODeviceForm::createArduinoDeviceTypeIOComboBox() {
    ioDeviceTypeList = ioDeviceRepository->getArduinoIODeviceTypes(arduino->id);
    for (auto &ioDeviceType: ioDeviceTypeList) {
        ui->comboBoxIODevices->addItem(ioDeviceType.type);
    }
}

void IODeviceForm::updateArduinoDeviceTypeIOComboBox(Arduino &_arduino) {
    ui->comboBoxIODevices->clear();
    ioDeviceTypeList.clear();
    arduino = &_arduino;
    ioDeviceTypeList = ioDeviceRepository->getArduinoIODeviceTypes(arduino->id);
    for (auto &ioDeviceType: ioDeviceTypeList) {
        ui->comboBoxIODevices->addItem(ioDeviceType.type, ioDeviceType.id);
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
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::DETECTIONSENSOR);
}

void IODeviceForm::createRelayFormWidgets() {
    qDebug("%s", qUtf8Printable("creating relay widgets..."));
    int maxColumnCount = 2;
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::RELAY);
}

void IODeviceForm::createIODeviceWidgets(int maxColumnCount, int ioDeviceType) {
    int column = 0, row = 0;

    for (auto ioDevice: ioDeviceList) {
        if (column == maxColumnCount) {
            column = 0;
            row++;
        }
        auto *ioDeviceForm = IODeviceFormFactory::getIODeviceForm(ioDeviceType, parent, &ioDevice);
        grid->addWidget(ioDeviceForm, row, column, Qt::AlignLeft);
        column++;
    }
    grid->setSizeConstraint(QLayout::SetMinimumSize);
}

void IODeviceForm::killChildWidgets() {
    QLayoutItem *child;
    while ((child = layout()->takeAt(0)) != 0) {
        //setLayout in constructor makes sure that when deleteLater is called on a child widget, it will be marked for delete
        child->widget()->deleteLater();
        qDebug("%s", qUtf8Printable("child deleted"));
    }
}

/* PRIVATE SLOTS */
void IODeviceForm::createIODeviceTypeFormList(const QString &deviceType) {
    killChildWidgets();
    ioDeviceList.clear();

    qDebug("%s", qUtf8Printable(deviceType));

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
