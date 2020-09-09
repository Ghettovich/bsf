#include "statemachinepage.h"
#include <repo/arduinorepo.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QIcon>


StateMachinePage::StateMachinePage(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f) {
    //vBoxLayout = new QVBoxLayout;
    gridLayout = new QGridLayout;
    setLayout(gridLayout);
}

void StateMachinePage::createArduinoBinAndLiftGroupBox() {
    ArduinoRepository arduinoRepository;
    arduinoBinAndLift = arduinoRepository.getActiveArduinoWithIODevices(arduinoBinAndLiftId);

    binAndLiftGroupBox = new QGroupBox;
    binAndLiftGroupBox->setTitle(arduinoBinAndLift.getName());

    arduinoBinAndLiftFormLayout = new QFormLayout(binAndLiftGroupBox);

    QIcon powerOFF(":/notification/power_off_black_48dp.png");

    btnStatusBinAndLift = new QPushButton;
    createArduinoStatusButton(btnStatusBinAndLift, arduinoBinAndLift.getArduinoState());

    arduinoBinAndLiftFormLayout->addRow(new QLabel("Status: "), btnStatusBinAndLift);
    arduinoBinAndLiftFormLayout->addRow(new QLabel(QString("Status bericht: ").append(arduinoBinAndLift.getStatusMessage())));
    arduinoBinAndLiftFormLayout->addRow(new QLabel(QString("Arduino omschrijving: ").append(arduinoBinAndLift.getDesc())));

    addIODevicesToGrid(arduinoBinAndLiftFormLayout, arduinoBinAndLift);
    printf("\nAdded arduino");

    // Add groupbox to grid
    gridLayout->addWidget(binAndLiftGroupBox, gridRowCount, gridColumnCount);
    gridColumnCount++;
}

void StateMachinePage::updateArduinoBinAndLiftGroupBox(Arduino::ARDUINO_STATE newState) {

}

void StateMachinePage::createArduinoWeightstationGroupBox() {
    ArduinoRepository arduinoRepository;
    arduinoWeightstation = arduinoRepository.getActiveArduinoWithIODevices(arduinoBinAndLiftId);

    weightstationGroupBox = new QGroupBox;
    weightstationGroupBox->setTitle(arduinoWeightstation.getName());

    arduinoWeightstationFormLayout = new QFormLayout(weightstationGroupBox);

    btnStatusWeightstation = new QPushButton;
    createArduinoStatusButton(btnStatusWeightstation, arduinoWeightstation.getArduinoState());

    arduinoWeightstationFormLayout->addRow(new QLabel("Status: "), btnStatusWeightstation);
    arduinoWeightstationFormLayout->addRow(new QLabel(QString("Status bericht: ").append(arduinoWeightstation.getStatusMessage())));
    arduinoWeightstationFormLayout->addRow(new QLabel(QString("Arduino omschrijving: ").append(arduinoWeightstation.getDesc())));

    addIODevicesToGrid(arduinoWeightstationFormLayout, arduinoWeightstation);

    // Add groupbox to grid
    gridLayout->addWidget(weightstationGroupBox, gridRowCount, gridColumnCount);
    gridColumnCount++;
}

void StateMachinePage::updateArduinoWeightstationGroupBox() {

}

void StateMachinePage::deleteChildrenFromGrid() {
    // ToDo: verify if all children are deleted from grid
    // verify if widgets from added layouts (like hbox ->addLayout(gridLayout) are correctly deleted
    while (!gridLayout->isEmpty()) {
        auto w = gridLayout->takeAt(0)->widget();
        w->deleteLater();
        printf("\nDeleted child in statemachine tab");
    }
}

void StateMachinePage::addIODevicesToGrid(QFormLayout *formLayout, Arduino arduino) {
    printf("\nDefault page arduino id: %d", arduino.getId());
    QIcon iconFound(":/actions/check_circle_black_48dp.png");
    QIcon iconNotFound(":/actions/highlight_off_black_48dp.png");

    if (arduino.hasRelayIODevices()) {
        formLayout->addRow(new QLabel("Relays: "), new QPushButton(iconFound, ""));
    } else {
        printf("\nno relays");
        formLayout->addRow(new QLabel("Relays: "), new QPushButton(iconNotFound, ""));
    }

    if (arduino.hasDetectionSensorIODevices()) {
        formLayout->addRow(new QLabel("Detection sensors: "), new QPushButton(iconFound, ""));
    } else {
        printf("\nno detection sensors");
        formLayout->addRow(new QLabel("Detection sensors: "), new QPushButton(iconNotFound, ""));
    }

    if (arduino.hasWeightSensorIODevices()) {
        formLayout->addRow(new QLabel("Weight sensors: "), new QPushButton(iconFound, ""));
    } else {
        formLayout->addRow(new QLabel("Weight sensors: "), new QPushButton(iconNotFound, ""));
    }
}

void StateMachinePage::createArduinoStatusButton(QPushButton *pushButton, Arduino::ARDUINO_STATE state) {
    if (state == Arduino::UNKOWN) {
        QIcon powerOFF(":/notification/power_off_black_48dp.png");
        pushButton->setStatusTip("Arduino NIET beschikbaar");
        pushButton->setIcon(powerOFF);
    } else if (state == Arduino::READY) {
        QIcon powerON(":/notification/power_on_black_48dp.png");
        pushButton->setStatusTip("Arduino beschikbaar");
        pushButton->setIcon(powerON);
    }
}

/** PUBLIC SLOTS */
void StateMachinePage::updateArduinoWithIODeviceList(int arduinoId, Arduino::ARDUINO_STATE newState,
                                                     const QVector<IODevice *> &ioDeviceList) {
    if(arduinoId == arduinoBinAndLift.getId()) {
        arduinoBinAndLift.setArduinoState(newState);
        arduinoBinAndLift.updateIODeviceList(ioDeviceList);

        createArduinoStatusButton(btnStatusBinAndLift, arduinoBinAndLift.getArduinoState());
    } else if(arduinoId == arduinoWeightstationId) {

    } else {
        printf("\nCould not find id of arduino to update.");
    }
}

void StateMachinePage::initializePage() {
    createArduinoBinAndLiftGroupBox();
    createArduinoWeightstationGroupBox();

    printf("\nBefore EMIT id = %d", arduinoBinAndLift.getId());
    emit requestIODeviceStates(arduinoBinAndLift);
}
