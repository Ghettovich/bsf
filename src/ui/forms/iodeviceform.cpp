#include "ui_iodeviceform.h"
#include "iodeviceform.h"
#include <repo/arduinorepo.h>
#include <repo/iodevicerepo.h>
#include <QVariant>
#include <utility>

IODeviceForm::IODeviceForm(QWidget *parent, const Qt::WindowFlags &f) :
        QWidget(parent, f)
        , payloadService(this)
        , networkService(this)
        , ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    ioDeviceList = QVector<IODevice *>();
    vbox = new QVBoxLayout(this);
    vbox->addWidget(ui->comboBoxIODevices, 0, Qt::AlignLeft);
    vbox->addWidget(ui->groupBoxConnectedIO);

    // LAYOUT
    grid = new QGridLayout(ui->groupBoxConnectedIO);
    //grid->setContentsMargins(10, 50, 10, 10);

    // SIGNALS & SLOTS
    // COMBO BOX
    connect(ui->comboBoxIODevices, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onCreateIODeviceTypeFormList(int)));

    QObject::connect(&networkService, &NetworkService::sendIODeviceListWithNewStates,
                     this, &IODeviceForm::onUpdateWithNewStateIODevice);
}

IODeviceForm::~IODeviceForm() {
    delete ui;
}

/** PRIVATE METHODS */
void IODeviceForm::createIODeviceWidgets() {

    int column = 0, row = 0, maxColumnCount = 2;

    for (auto ioDevice: ioDeviceList) {
        if (column == maxColumnCount) {
            column = 0;
            row++;
        }
        if(selectedIODeviceType.getIODeviceType() == IODeviceType::RELAY) {
            printf("\nCreating forms for RELAY");
            auto relayForm = new RelayForm(this, Qt::Widget, dynamic_cast<Relay &>(*ioDevice));
            //relayWidgetList.append(relayForm);
            grid->addWidget(relayForm, row, column, Qt::AlignLeft);
            printf("\nAdded to grid");
        }
        else if (selectedIODeviceType.getIODeviceType() == IODeviceType::DETECTIONSENSOR) {
            printf("\nCreating forms for DETECTION SENSOR");
            auto detectSensorForm = new DetectionSensorForm(this, Qt::Widget,
                                                            dynamic_cast<DetectionSensor &>(*ioDevice));
            //detetectionSensorWidgetList.append(detectSensorForm);
            grid->addWidget(detectSensorForm, row, column, Qt::AlignLeft);
        }
        else if (selectedIODeviceType.getIODeviceType() == IODeviceType::WEIGHTSENSOR) {
            printf("\nCreating forms for WEIGHT SENSOR");
            auto weightSensorForm = new WeightSensorForm(this, Qt::Widget, dynamic_cast<WeightCensor &>(*ioDevice));
            //weightSensorWidgetList.append(weightSensorForm);
            grid->addWidget(weightSensorForm, row, column, Qt::AlignLeft);
        }
        column++;
    }
    ui->groupBoxConnectedIO->layout()->setSizeConstraint(QLayout::SetMinimumSize);
}

void IODeviceForm::killChildWidgets() {
    while (!grid->isEmpty()) {
        auto widget = grid->takeAt(0)->widget();
        widget->deleteLater();
        printf("\nchild deleted in ioDeviceForm");
    }
}

void IODeviceForm::createIODeviceWidgetsFromSelectedIndex() {
    if(ui->comboBoxIODevices->currentIndex() >= 0) {

    }
}

/** PUBLIC METHODS */
void IODeviceForm::onCreateArduinoDeviceTypeIOComboBox(Arduino &_arduino, QVector<IODeviceType> _ioDeviceTypeList) {
    arduino = _arduino;
    ioDeviceTypeList = std::move(_ioDeviceTypeList);
    //printf("\n(IODeviceForm-->oncreate) io device list size = %s", _ioDeviceTypeList.size());

    if (!ioDeviceTypeList.empty()) {
        printf("\nio device type list not empty");

        ui->comboBoxIODevices->clear();
        selectedIODeviceType = ioDeviceTypeList.first();
        ui->comboBoxIODevices->setEnabled(true);
        for (auto &j : ioDeviceTypeList) {
            ui->comboBoxIODevices->addItem(j.getType());
        }

    } else {
        printf("\nNo io device types");
        ui->comboBoxIODevices->setEnabled(false);
    }
    printf("\nEnd method");
}



void IODeviceForm::onCreateIODeviceTypeFormList(int index) {
    if (index >= 0) {
        killChildWidgets();
        ioDeviceList.clear();
        //printf("\nGOT INDEX = %s", index);
        selectedIODeviceType = ioDeviceTypeList[index];

        if(selectedIODeviceType.getId() > 0) {
            printf("\nGot valid io device type id");
            IODeviceRepository ioDeviceRepository;
            //ioDeviceList = QVector<IODevice *>();
            ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduino.getId()
                    , selectedIODeviceType.getId()
                    , selectedIODeviceType.getIODeviceType());
            createIODeviceWidgets();
        }
        else {
            printf("\nUnknown ID");
        }
    }
}

void IODeviceForm::onSendRequest(const QUrl &url) {
    networkService.requestPayload(url);
    qDebug() << "Url = " << url.toString();
}

void IODeviceForm::onUpdateWithNewStateIODevice(QVector<IODevice *> _ioDeviceList) {
//    ioDeviceList = std::move(_ioDeviceList);
    qDebug("got new list...");
//    if (selectedIODeviceType.getIODeviceType() == IODeviceType::WEIGHTSENSOR) {
//        //update weight sensor list here
//
//
//    } else {
//        // update iodevice here
//        if (!ioDeviceList.empty() &&
//            selectedIODeviceType.getIODeviceType() == IODeviceType::RELAY)
//            for (auto widget : relayWidgetList) {
//                for (const auto &ioDevice : ioDeviceList) {
//                    if (widget->property("relay-id") == ioDevice.getId()) {
//                        widget->setIODeviceState(ioDevice.getDeviceState());
//                    }
//                }
//            }
//
//    }

}


