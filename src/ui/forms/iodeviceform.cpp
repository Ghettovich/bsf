#include <ui_iodeviceform.h>
#include <incl/ui/forms/iodeviceform.h>
#include <incl/ui/forms/weightsensorform.h>
#include <incl/ui/forms/detectionsensorform.h>
#include <incl/ui/forms/relayform.h>
#include <QtWidgets/QScrollArea>

IODeviceForm::IODeviceForm(QWidget *_parent, Arduino *_arduino) :
        QWidget(_parent), ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    parent = _parent;
    arduino = _arduino;
    grid = new QGridLayout(this);
    grid->setContentsMargins(10, 50, 3, 5);
    //setLayout(grid);

    ioDeviceRepository = new IODeviceRepository;
    setGeometry(310, 0, 694, 480);
    createArduinoDeviceTypeIOComboBox();
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
        qDebug("%s", qUtf8Printable("creating sensor widgets..."));
        if (column == maxColumnCount) {
            column = 0;
            row++;
            qDebug("%s", qUtf8Printable("set col to 0, increase rowcount"));
        }

        auto *form = new QWidget;
        switch (ioDeviceType) {
            case IODeviceTypeEnum::WEIGHTSENSOR :
                form = new WeightSensorForm(this, &ioDevice);
                break;
            case IODeviceTypeEnum::DETECTIONSENSOR :
                form = new DetectionSensorForm(this, &ioDevice);
                break;
            case IODeviceTypeEnum::RELAY :
                form = new RelayForm(this);
                break;
            default:
                qDebug("%s", qUtf8Printable("Could not find matching device type"));
                break;
        }

        ioDeviceFormList.append(form);
        grid->addWidget(form, row, column, Qt::AlignLeft);
        column++;
    }
}

void IODeviceForm::killChildWidgets() {
    QLayoutItem *child;
    while ((child = layout()->takeAt(0)) != 0) {
        child->widget()->deleteLater();
        qDebug("%s", qUtf8Printable("child deleted"));
    }
    ioDeviceFormList.clear();
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
