#include "deviceactionform.h"

#include <utility>
#include "ui_deviceactionform.h"
#include "iodeviceform.h"

DeviceActionForm::DeviceActionForm(QWidget *parent) :
        QWidget(parent), ui(new Ui::DeviceActionForm) {
    ui->setupUi(this);

    qDebug("%s", qUtf8Printable("entered constructor device form"));
    // update combobox io devices types

    // SIGNALS & SLOTS
    connect(ui->comboBoxArduino, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateWidget(int)));
}

DeviceActionForm::~DeviceActionForm() {
    delete ui;
}

void DeviceActionForm::createComboBoxItems(QList<Arduino> _arduinoList) {
    arduinoList = std::move(_arduinoList);
    for (const Arduino &a : arduinoList) {
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
        newListItem->setText(i.getCode());
        newListItem->setData(Qt::UserRole, i.getId());
        ui->listWidget->addItem(newListItem);
    }
}


void DeviceActionForm::updateLabels() {
    ui->labelArduinoDescription->setText(arduino.desc);
    ui->labelArduinoIp->setText(arduino.ipAddress);
}

void DeviceActionForm::updateWidget(int index) {
    // Id is stored with Qt::UserRole
    QVariant id = ui->comboBoxArduino->currentData(Qt::UserRole);

    qDebug("index = %s", qUtf8Printable(QString::number(index)));
    qDebug("qvariant id = %s", qUtf8Printable(id.toString()));

    ui->listWidget->clear();
    actionList.clear();

    for (auto &_arduino: arduinoList) {
        if (_arduino.id == id) {
            arduino = _arduino;
            actionList = actionArduinoRepository.getArduinoAction(arduino.id);
            createListWidget(actionList);
            updateLabels();
            //emit arduinoIdChange(arduino.id);
            break;
        }
    }
}

int DeviceActionForm::selectedArduinoId() {
    return arduino.id > 0 ? arduino.id : 0;
}

