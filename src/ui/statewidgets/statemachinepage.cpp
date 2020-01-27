#include "statemachinepage.h"
#include <repo/arduinorepo.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QIcon>


StateMachinePage::StateMachinePage(QVBoxLayout *layout, const Qt::WindowFlags &f) {
    tabWidgetIODevices = new QTabWidget;
    gridLayout = new QGridLayout;
    layout->addWidget(tabWidgetIODevices);
    createTabwidgetIODevices();

}

void StateMachinePage::createTabwidgetIODevices() {

    tabWidgetIODevices->setTabPosition(QTabWidget::West);
    QObject::connect(tabWidgetIODevices, &QTabWidget::currentChanged,
                     this, &StateMachinePage::onChangeIndexTabWidgetIODevices);

    tabWidgetIODevices->show();

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
    ArduinoRepository arduinoRepository;
    arduinoList = arduinoRepository.getAllActiveArduinoWithIODevices();
    defaultPage->setLayout(gridLayout);

    int colCount = 0, rowCount = 0;
    for(auto arduino : arduinoList) {
        auto btnStatusArduino = new QPushButton;
        if (arduino->getArduinoState() == Arduino::UNKOWN) {
            QIcon powerOFF(":/notification/power_off_black_48dp.png");
            btnStatusArduino->setIcon(powerOFF);
        } else if (arduino->getArduinoState() == Arduino::READY) {
            QIcon powerON(":/notification/power_on_black_48dp.png");
            btnStatusArduino->setIcon(powerON);
        }
        gridLayout->addWidget(btnStatusArduino, rowCount, colCount, Qt::AlignLeft);
        rowCount++;
        // Widget zero
        auto lblNameArduino = new QLabel(arduino->getName());
        gridLayout->addWidget(lblNameArduino, rowCount, colCount, Qt::AlignLeft);
        rowCount++;
        auto lblStatus = new QLabel(QString("Status: ").append(arduino->getStatusMessage()));
        gridLayout->addWidget(lblStatus, rowCount, colCount, Qt::AlignLeft);
        rowCount++;


        auto lblDescArduino = new QLabel(arduino->getDesc());
        gridLayout->addWidget(lblDescArduino, rowCount, colCount, Qt::AlignLeft);
        rowCount++;

        addIODevicesToGrid(gridLayout, arduino, rowCount, colCount);
        printf("\nAdded arduino");
        colCount++;
        rowCount = 0;
    }

    tabWidgetIODevices->setCurrentWidget(defaultPage);
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
void StateMachinePage::onChangeIndexTabWidgetIODevices(int index) {

    if(index == 0)
        createDefaultPage();
}
void StateMachinePage::addIODevicesToGrid(QGridLayout *grid, Arduino *arduino, int rowCount, int colCount) {
    printf("\nAdding iodevice");
    bool isRelayLow = false;
    for(auto ioDevice : * arduino->getIoDeviceList()) {

        if(ioDevice->getDeviceState() == IODevice::LOW) {
            isRelayLow = true;
        }
    }

    auto btnStatus = new QPushButton;
    if(isRelayLow) {
        QIcon icon(":/alert/warning_amber_48pt.png");
        btnStatus->setIcon(icon);
    } else {
        QIcon icon(":/actions/check_circle_black_48dp.png");
        btnStatus->setIcon(icon);
    }

    grid->addWidget(btnStatus, rowCount, colCount, Qt::AlignLeft);
}


