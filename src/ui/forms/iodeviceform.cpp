#include <ui_iodeviceform.h>
#include <incl/ui/forms/iodeviceform.h>

IODeviceForm::IODeviceForm(QWidget *_parent, Arduino *_arduino) :
        QWidget(_parent), ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    parent = _parent;
    arduino = _arduino;
    ioDeviceRepository = new IODeviceRepository;
    setGeometry(310, 0, 694, 480);
    createArduinoDeviceTypeIOComboBox();
}

IODeviceForm::~IODeviceForm() {
    delete ui;
}

void IODeviceForm::createArduinoDeviceTypeIOComboBox() {
    ioDeviceTypeList = ioDeviceRepository->getArduinoIODeviceTypes(arduino->id);
    for(auto &ioDeviceType: ioDeviceTypeList) {
        ui->comboBoxIODevices->addItem(ioDeviceType.type);
    }
}

void IODeviceForm::updateArduinoDeviceTypeIOComboBox(Arduino &_arduino) {
    ui->comboBoxIODevices->clear();
    ioDeviceTypeList.clear();
    arduino = &_arduino;
    ioDeviceTypeList = ioDeviceRepository->getArduinoIODeviceTypes(arduino->id);
    for(auto &ioDeviceType: ioDeviceTypeList) {
        ui->comboBoxIODevices->addItem(ioDeviceType.type);
    }
}
