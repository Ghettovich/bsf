#include "statemachinepage.h"
#include <repo/arduinorepo.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QIcon>


StateMachinePage::StateMachinePage(QVBoxLayout *layout, const Qt::WindowFlags &f) {
    tabWidgetIODevices = new QTabWidget;
    gridLayout = new QGridLayout;
    layout->addWidget(tabWidgetIODevices);
    tabWidgetIODevices->show();

    // request state for each arduino and update accordingly...
    networkService = new NetworkService(defaultPage);
    QObject::connect(networkService, &NetworkService::sendArduinoWithNewStates,
                     this, &StateMachinePage::updateArduinoWithIODeviceList);

    QString hostAddress = "fe80::2c7d:fdff:fe96:c398";
    Recipe recipe = Recipe(1);

    payloadService = new PayloadService(defaultPage);
    payloadService->broadcastRecipe(recipe, hostAddress);

    ArduinoRepository arduinoRepository;
    arduinoList = arduinoRepository.getAllActiveArduinoWithIODevices();

    createTabwidgetIODevices();
    createDefaultPage();

    // ToDo: add error handling
    networkService->requestPayload(arduinoList[0]);
}

void StateMachinePage::createArduinoBinAndLiftGroupBox() {
    ArduinoRepository arduinoRepository;
    arduinoBinAndLift = arduinoRepository.getArduino(arduinoBinAndLiftId);

    binAndLiftGroupBox = new QGroupBox;
    binAndLiftGroupBox->setTitle(arduinoBinAndLift.getName());

    arduinoBinAndLiftFormLayout = new QFormLayout(binAndLiftGroupBox);

    QIcon powerOFF(":/notification/power_off_black_48dp.png");

    btnStatusBinAndLift = new QPushButton;
    btnStatusBinAndLift->setStatusTip("Arduino NIET beschikbaar");
    btnStatusBinAndLift->setIcon(powerOFF);

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

}

void StateMachinePage::updateArduinoWeightstationGroupBox() {

}

void StateMachinePage::createTabwidgetIODevices() {
    tabWidgetIODevices->setTabPosition(QTabWidget::West);
    QObject::connect(tabWidgetIODevices, &QTabWidget::currentChanged,
                     this, &StateMachinePage::onChangeIndexTabWidgetIODevices);

    defaultPage = new QWidget;
    tabWidgetIODevices->addTab(defaultPage, "Start");
    weightSensorPage = new QWidget;
    tabWidgetIODevices->addTab(weightSensorPage, "Weegcellen");
    detectionSensorPage = new QWidget;
    tabWidgetIODevices->addTab(detectionSensorPage, "Sensoren");
    relayPage = new QWidget;
    tabWidgetIODevices->addTab(relayPage, "Relay");
    bunkerPage = new QWidget;
    tabWidgetIODevices->addTab(bunkerPage, "Bunkers");
}

void StateMachinePage::createDefaultPage() {
    printf("\ncreating default page");

    defaultPage->setLayout(gridLayout);
    if(arduinoList.empty()) {
        printf("\nGot empty arduino list!!");
    } else {
        int colCount = 0, rowCount = 0;
        for (auto arduino : arduinoList) {
            auto groupBox = new QGroupBox;
            groupBox->setTitle(arduino->getName());
            auto formLayout = new QFormLayout(groupBox);

            auto btnStatusArduino = new QPushButton;
            if (arduino->getArduinoState() == Arduino::UNKOWN) {
                QIcon powerOFF(":/notification/power_off_black_48dp.png");
                btnStatusArduino->setStatusTip("Arduino NIET beschikbaar");
                btnStatusArduino->setIcon(powerOFF);
            } else if (arduino->getArduinoState() == Arduino::READY) {
                QIcon powerON(":/notification/power_on_black_48dp.png");
                btnStatusArduino->setStatusTip("Arduino beschikbaar");
                btnStatusArduino->setIcon(powerON);
            }
            formLayout->addRow(new QLabel("Status: "), btnStatusArduino);
            formLayout->addRow(new QLabel(QString("Status bericht: ").append(arduino->getStatusMessage())));
            formLayout->addRow(new QLabel(QString("Arduino omschrijving: ").append(arduino->getDesc())));

            addIODevicesToGrid(formLayout, *arduino);
            printf("\nAdded arduino");

            // Add groupbox to grid
            gridLayout->addWidget(groupBox, rowCount, colCount);
            colCount++;
            //rowCount = 0;

        }

        tabWidgetIODevices->setCurrentWidget(defaultPage);
    }
}

void StateMachinePage::createDetectionSensorPage() {
//    auto lblSensor1 = new QLabel("Weeg cell 1");
//    gridLayout->addWidget(lblSensor1, 0, 0, Qt::AlignLeft);
//    detectionSensorPage->setLayout(gridLayout);
//    tabWidgetIODevices->setCurrentWidget(weightSensorPage);
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

/** PUBLIC SLOTS */
void StateMachinePage::onChangeIndexTabWidgetIODevices(int index) {
    printf("\nId = %d", arduinoList[0]->getId());

//    deleteChildrenFromGrid();
//
//    if (index == 0) {
//        printf("\nState machine page tab widget index change");
//        createDefaultPage();
//    }
}

void StateMachinePage::updateArduinoWithIODeviceList(int arduinoId, Arduino::ARDUINO_STATE newState,
                                                     const QVector<IODevice *> &ioDeviceList) {
    for (auto arduino : arduinoList) {
        if (arduino->getId() == arduinoId) {
            arduino->setArduinoState(newState);
            arduino->updateIODeviceList(ioDeviceList);

            if(arduinoId == arduinoBinAndLiftId) {

            }
        }
    }
}

