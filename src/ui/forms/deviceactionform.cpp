#include <ui_deviceactionform.h>
#include <QtGlobal>
#include <incl/ui/forms/deviceactionform.h>

DeviceActionForm::DeviceActionForm(QWidget *_parent) :
        QWidget(_parent), ui(new Ui::DeviceActionForm) {
    ui->setupUi(this);
    parent = _parent;
    arduinoRepository = new ArduinoRepository;
    actionArduinoRepository = new ActionArduinoRepository;
    arduinoList = arduinoRepository->getAllActiveArduino();

    if (arduinoList.length() > 0) {
        selectedArduino = arduinoList.first();
    }

    createComboBoxItems();
    createStateActionItemList();
    createIODeviceForm();

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
    if (selectedArduino.id > 0) {
        actionList = actionArduinoRepository->getArduinoAction(selectedArduino.id);
        for (auto &i : actionList) {
            auto *newListItem = new QListWidgetItem;
            newListItem->setText(QStringLiteral("%1 %2").arg(i.code, i.description));
            ui->listWidget->addItem(newListItem);
        }
    } else {
        ui->comboBoxArduino->addItem("Could not get arduino id...");
    }
}

void DeviceActionForm::createIODeviceForm() {
    ioDeviceForm = new IODeviceForm(parent, &selectedArduino);
}

void DeviceActionForm::updateIODeviceForm() {
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
