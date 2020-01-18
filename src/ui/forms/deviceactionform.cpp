#include "deviceactionform.h"

#include <utility>
#include "ui_deviceactionform.h"
#include "iodeviceform.h"

DeviceActionForm::DeviceActionForm(QWidget *parent) :
        QWidget(parent)
        , ui(new Ui::DeviceActionForm) {
    ui->setupUi(this);

    qDebug("%s", qUtf8Printable("entered constructor device form"));
    // update combobox io devices types

    // SIGNALS & SLOTS
    connect(ui->comboBoxArduino, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateWidget(int)));

    QObject::connect(this, SIGNAL(arduinoIdChange(int arduinoId)),
            SLOT(&IODeviceForm::onCreateArduinoDeviceTypeIOComboBox(int arduinoId)));
}

DeviceActionForm::~DeviceActionForm() {
    delete ui;
}

void DeviceActionForm::createComboBoxItems(QList<Arduino> _arduinoList) {
    arduinoList = std::move(_arduinoList);
    for (const Arduino& a : arduinoList) {
        ui->comboBoxArduino->addItem(a.name, a.id);
    }
    updateLabels();
}

void DeviceActionForm::createStateActionItemList(Arduino _selectedArduino, QList<Action> _actionList) {
    arduino = std::move(_selectedArduino);
    actionList = std::move(_actionList);
    createListWidget(actionList);
}

void DeviceActionForm::createListWidget(QList<Action> _actionList) {
    actionList = std::move(_actionList);
    for (auto &i : actionList) {
        auto *newListItem = new QListWidgetItem;
        newListItem->setText(i.code);
        newListItem->setData(Qt::UserRole, i.id);
        ui->listWidget->addItem(newListItem);
    }
}


void DeviceActionForm::updateLabels() {
    ui->labelArduinoDescription->setText(arduino.desc);
    ui->labelArduinoIp->setText(arduino.ipAddress);
}

void DeviceActionForm::updateWidget(int arduinoId) {

    qDebug("update widget arduino is = %s", qUtf8Printable(QString::number(arduinoId)));

    if(arduinoId > 0 && arduino.id != arduinoId) {
        ui->listWidget->clear();
        actionList.clear();
        for (auto &_arduino: arduinoList) {
            if (_arduino.id == arduinoId) {
                arduino = _arduino;
                break;
            }
        }
        actionList = actionArduinoRepository.getArduinoAction(arduino.id);
        createListWidget(actionList);
        updateLabels();
    }
}

int DeviceActionForm::selectedArduinoId() {
    return arduino.id > 0 ? arduino.id : 0;
}

