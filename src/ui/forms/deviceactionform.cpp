#include "deviceactionform.h"
#include "ui_deviceactionform.h"


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

void DeviceActionForm::createComboBoxItems(QVector<Arduino> _arduinoList) {
    arduinoList = std::move(_arduinoList);
    arduino = arduinoList.first();

    for (const Arduino &a : arduinoList) {
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
        qDebug("adding list item");
    }
}


void DeviceActionForm::updateLabels() {
    ui->labelArduinoDescription->setText(arduino.getDesc());
    ui->labelArduinoIp->setText(arduino.getIpAddress());
}

void DeviceActionForm::updateWidget(int index) {
    // Id is stored with Qt::UserRole
    QVariant id = ui->comboBoxArduino->currentData(Qt::UserRole);

    qDebug("index = %s", qUtf8Printable(QString::number(index)));
    qDebug("qvariant id = %s", qUtf8Printable(id.toString()));

    ui->listWidget->clear();
    actionList.clear();

    for (auto &_arduino: arduinoList) {
        if (_arduino.getId() == id) {
            arduino = _arduino;
            actionList = actionArduinoRepository.getArduinoAction(arduino.getId());
            createListWidget();
            updateLabels();
            //emit arduinoIdChange(arduino.id);
            break;
        }
    }
}

Arduino& DeviceActionForm::selectedArduino() {
    return arduino;
}

