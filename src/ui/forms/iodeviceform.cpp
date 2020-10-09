#include "ui_iodeviceform.h"
#include "iodeviceform.h"
#include <repo/arduinorepo.h>
#include <repo/statecoderepo.h>
#include <repo/iodevicerepo.h>
#include <QVariant>
#include <utility>

IODeviceForm::IODeviceForm(QWidget *parent, const Qt::WindowFlags &f) :
        QWidget(parent, f)
        , payloadService(this)
        , networkService(this)
        , localSocket(this)
        , ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    ioDeviceList = QVector<IODevice *>();
    vbox = new QVBoxLayout(this);
    vbox->addWidget(ui->comboBoxIODevices, 0, Qt::AlignLeft);
    vbox->addWidget(ui->groupBoxConnectedIO);

    // LAYOUT
    grid = new QGridLayout(ui->groupBoxConnectedIO);

    // SIGNALS & SLOTS
    // COMBO BOX
    connect(ui->comboBoxIODevices, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onCreateIODeviceTypeFormList(int)));

    QObject::connect(&networkService, &NetworkService::sendArduinoWithNewStates,
                     this, &IODeviceForm::onUpdateIODeviceWidgets);

    QObject::connect(&payloadService, &PayloadService::receivedIODevicesWithNewState,
            this, &IODeviceForm::onUpdateIODeviceWidgets);

    connect(&payloadService, &PayloadService::receivedUpdateForWeightSensor,
                     this, &IODeviceForm::onUpdateWeightSensor);
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
            auto relayForm = new RelayForm(this, Qt::Widget
                    , dynamic_cast<Relay &>(*ioDevice));
            QObject::connect(relayForm, &RelayForm::sendRequest, this, &IODeviceForm::onSendRequest);
            relayWidgetList.append(relayForm);
            grid->addWidget(relayForm, row, column, Qt::AlignLeft);
        }
        else if (selectedIODeviceType.getIODeviceType() == IODeviceType::DETECTIONSENSOR) {
            auto detectSensorForm = new DetectionSensorForm(this, Qt::Widget
                    , dynamic_cast<DetectionSensor &>(*ioDevice));
            detetectionSensorWidgetList.append(detectSensorForm);
            grid->addWidget(detectSensorForm, row, column, Qt::AlignLeft);
        }
        else if (selectedIODeviceType.getIODeviceType() == IODeviceType::WEIGHTSENSOR) {
            auto weightSensorForm = new WeightSensorForm(this, Qt::Widget
                    , dynamic_cast<WeightSensor &>(*ioDevice));
            QObject::connect(weightSensorForm, &WeightSensorForm::broadcastRecipe,
                             this, &IODeviceForm::onBroadcastRecipe);
            weightSensorWidgetList.append(weightSensorForm);
            grid->addWidget(weightSensorForm, row, column, Qt::AlignLeft);
        }
        column++;
    }
    ui->groupBoxConnectedIO->layout()->setSizeConstraint(QLayout::SetMinimumSize);
    updateWidgetsWithState();
}

void IODeviceForm::killChildWidgets() {
    while (!grid->isEmpty()) {
        auto widget = grid->takeAt(0)->widget();
        widget->deleteLater();
    }
}

/** PUBLIC METHODS */
void IODeviceForm::onCreateArduinoDeviceTypeIOComboBox(Arduino &_arduino, QVector<IODeviceType> _ioDeviceTypeList) {
    arduino = _arduino;
    ioDeviceTypeList = std::move(_ioDeviceTypeList);

    if (!ioDeviceTypeList.empty()) {
        ui->comboBoxIODevices->clear();
        selectedIODeviceType = ioDeviceTypeList.first();
        ui->comboBoxIODevices->setEnabled(true);
        for (auto &j : ioDeviceTypeList) {
            ui->comboBoxIODevices->addItem(j.getType());
        }

    } else {
        ui->comboBoxIODevices->setEnabled(false);
    }
}

void IODeviceForm::onCreateIODeviceTypeFormList(int index) {
    if (index >= 0) {
        killChildWidgets();
        ioDeviceList.clear();
        relayWidgetList.clear();
        weightSensorWidgetList.clear();
        detetectionSensorWidgetList.clear();
        selectedIODeviceType = ioDeviceTypeList[index];

        if(selectedIODeviceType.getId() > 0) {
            IODeviceRepository ioDeviceRepository;
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

/// ON SEND COMMENTED OUT!!
void IODeviceForm::updateWidgetsWithState() {
    networkService.requestPayload(arduino);
    //QUrl fullStateUrl = arduino.generateQUrl(); // QUrl("http://[" + arduino.getIpAddress() + "]/");
    //onSendRequest(fullStateUrl);
}

void IODeviceForm::onSendRequest(const QUrl& url) {
    //networkService.requestPayload(arduino, url);
}

void IODeviceForm::onUpdateIODeviceWidgets(int arduinoId, Arduino::ARDUINO_STATE newState, const QVector<IODevice *> & _ioDeviceList) {
    if(arduinoId == arduino.getId()) {
        arduino.setArduinoState(newState);

        StateCodeRepository stateCodeRepository;
        StateCode stateCode = stateCodeRepository.getStateCode(newState);

        setStatusTip(stateCode.getStatusMessage());

        if (selectedIODeviceType.getIODeviceType() == IODeviceType::WEIGHTSENSOR) {
            //update weight sensor list here
            for (WeightSensorForm *widget : weightSensorWidgetList) {
                for (auto weightSensor: _ioDeviceList) {
                }
            }
        } else if (selectedIODeviceType.getIODeviceType() == IODeviceType::RELAY) {

            for (auto widget : relayWidgetList) {
                for (auto relay: _ioDeviceList) {
                    if (widget->property("relay-id") == relay->getId()) {
                        widget->setIODeviceState(relay->getDeviceState());
                    }
                }
            }
        } else if (selectedIODeviceType.getIODeviceType() == IODeviceType::DETECTIONSENSOR) {

            for (auto widget : detetectionSensorWidgetList) {
                for (auto detectSensor: _ioDeviceList) {
                    if (widget->property("detectionsensor-id") == detectSensor->getId()) {
                        widget->updateDetectionSensor(detectSensor->getDeviceState());
                    }
                }
            }
        }
    } else {
        printf("\nid's do not match in onUpdateIODeviceWidgets (iodeviceform)");
    }
}

bool IODeviceForm::isIODeviceListEmpty() {
    return ioDeviceList.isEmpty();
}

void IODeviceForm::onUpdateWeightSensor(IODevice *ioDevice, Arduino::ARDUINO_STATE state) {
    if (selectedIODeviceType.getIODeviceType() == IODeviceType::WEIGHTSENSOR) {
        WeightSensor weightSensor = (WeightSensor &) *ioDevice;

        for(auto weightSensorWidget: weightSensorWidgetList) {
            if(weightSensorWidget->property("weightsensor-id") == ioDevice->getId()) {
                weightSensorWidget->updateWeightSensorForm(weightSensor, state);
            }
            else {
                printf("weightsensor id propery do not match.");
            }
        }
    } else {
        printf("\nSelect iodevice type id do not natch.");
    }

}

void IODeviceForm::onBroadcastRecipe(const Recipe& recipe) {
    payloadService.broadcastRecipe(recipe,
                                   arduino.getId(),
                                   arduino.getIpAddress(),
                                   arduino.getPort());
}
