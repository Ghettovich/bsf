#include "deviceactionform.h"
#include "ui_deviceactionform.h"


DeviceActionForm::DeviceActionForm(QWidget *parent, const Qt::WindowFlags &f) :
        QWidget(parent, f), ui(new Ui::DeviceActionForm) {
    ui->setupUi(this);

    // SIGNALS & SLOTS
    connect(ui->comboBoxArduino, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateWidget(int)));
}

DeviceActionForm::~DeviceActionForm() {
    delete ui;
}

void DeviceActionForm::createComboBoxItems(QVector<Arduino> _arduinoList) {
    arduinoList = std::move(_arduinoList);
    arduino = arduinoList.first();

    for (const auto& a : arduinoList) {
        ui->comboBoxArduino->addItem(a.getName(), a.getId());
    }
    updateLabels();
}

void DeviceActionForm::createStateActionItemList(QVector<Action>  _actionList) {
    actionList = std::move(_actionList);
}

void DeviceActionForm::createListWidget() {
    for (auto &i : actionList) {
        auto newListItem = new QListWidgetItem;
        newListItem->setText(i.getCode());
        newListItem->setData(Qt::UserRole, i.getId());
        ui->listWidget->addItem(newListItem);
    }
}

void DeviceActionForm::updateLabels() {
    ui->labelArduinoDescription->setText(arduino.getDesc());
    ui->labelArduinoIp->setText(arduino.getIpAddress());
}

void DeviceActionForm::updateWidget(int index) {
    // Id is stored with Qt::UserRole
    QVariant id = ui->comboBoxArduino->currentData(Qt::UserRole);

    ui->listWidget->clear();
    actionList.clear();

    for (auto &_arduino: arduinoList) {
        if (_arduino.getId() == id) {
            arduino = _arduino;
            actionList = actionArduinoRepository.getArduinoAction(arduino.getId());
            createListWidget();
            updateLabels();
            emit onSelectedArduinoChange(arduino.getId());
            break;
        }
    }
}

Arduino& DeviceActionForm::selectedArduino() {
    return arduino;
}

