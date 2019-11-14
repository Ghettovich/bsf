#include <ui_deviceactionform.h>
#include <incl/ui/forms/deviceactionform.h>

DeviceActionForm::DeviceActionForm(QWidget *_parent) :
        QWidget(_parent)
        , ui(new Ui::DeviceActionForm) {
    ui->setupUi(this);
    parent = _parent;
    arduinoRepository = new ArduinoRepository;
    actionArduinoRepository = new ActionArduinoRepository;

    lblIp = ui->labelArduinoIp;

    createComboBoxItems();
    createStateActionItemList();
}

DeviceActionForm::~DeviceActionForm() {
    delete ui;
}

void DeviceActionForm::createComboBoxItems() {
    arduinoList = arduinoRepository->getAllActiveArduino();
    if (arduinoList.length() > 0) {
        selectedArduino = arduinoList.first();

        //qDebug("%s", qUtf8Printable(selectedArduino.ipAddress));
        ui->labelArduinoDescription->setText(selectedArduino.desc);

        // This label... arrghh
        lblIp->setText("Wat een kanker label");

        for (const auto &a : arduinoList) {
            ui->comboBoxArduino->addItem(a.name);
        }
    }
}

void DeviceActionForm::createStateActionItemList() {
    if(selectedArduino.id > 0) {
        actionList = actionArduinoRepository->getArduinoAction(selectedArduino.id);
        for (auto & i : actionList) {
            ui->listWidget->addItem(i.code);
        }
    }
    else {
        ui->comboBoxArduino->addItem("Could not fetch arduinos...");
    }
}


