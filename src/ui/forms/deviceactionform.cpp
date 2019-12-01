#include <ui_deviceactionform.h>
#include <QtGlobal>
#include <incl/ui/forms/deviceactionform.h>

DeviceActionForm::DeviceActionForm(QWidget *_parent) :
        QWidget(_parent)
        , ui(new Ui::DeviceActionForm) {
    ui->setupUi(this);
    parent = _parent;
    arduinoRepository = new ArduinoRepository;
    actionArduinoRepository = new ActionArduinoRepository;
    arduinoList = arduinoRepository->getAllActiveArduino();

    qDebug("%s", qUtf8Printable("entered constructor device form"));

    if (arduinoList.length() > 0) {
        selectedArduino = arduinoList.first();
    }

    createComboBoxItems();
    createStateActionItemList();
    createIODeviceForm();

    // SIGNALS & SLOTS
    connect(ui->comboBoxArduino, SIGNAL(currentIndexChanged(const QString&)),this, SLOT(updateWidget(const QString&)));
}

DeviceActionForm::~DeviceActionForm() {
    delete ui;
}

void DeviceActionForm::createComboBoxItems() {
    for (const auto &a : arduinoList) {
        ui->comboBoxArduino->addItem(a.name);
    }
    updateLabels();
}

void DeviceActionForm::updateLabels() {
    ui->labelArduinoDescription->setText(selectedArduino.desc);
    ui->labelArduinoIp->setText(selectedArduino.ipAddress);
}

void DeviceActionForm::createStateActionItemList() {
    qDebug("%s", qUtf8Printable("creating state action item list"));
    if (selectedArduino.id > 0) {
        actionList = actionArduinoRepository->getArduinoAction(selectedArduino.id);
        for (auto &i : actionList) {
            auto *newListItem = new QListWidgetItem;
            newListItem->setText(i.code);
            ui->listWidget->addItem(newListItem);
        }
    } else {
        ui->comboBoxArduino->addItem("Could not get arduino id...");
    }
}

void DeviceActionForm::createIODeviceForm() {
    qDebug("%s", qUtf8Printable("creating  IODeviceForm"));
    ioDeviceForm = new IODeviceForm(parent, &selectedArduino);
}

void DeviceActionForm::updateIODeviceForm() {
    qDebug("%s", qUtf8Printable("update IODeviceForm (only combobox)"));
    ioDeviceForm->updateArduinoDeviceTypeIOComboBox(selectedArduino);
}

void DeviceActionForm::updateWidget(const QString &arduino_id) {
    ui->listWidget->clear();
    actionList.clear();

    for (auto &a: arduinoList) {
        if (a.name == arduino_id) {
            qDebug("%s is equal", qUtf8Printable(arduino_id));
            selectedArduino = a;
            updateLabels();
            createStateActionItemList();
            updateIODeviceForm();
        }
    }
}
