#include "statemachinepage.h"
#include <QtWidgets/QLabel>

StateMachinePage::StateMachinePage(QVBoxLayout *layout, const Qt::WindowFlags &f) {
    tabWidgetIODevices = new QTabWidget;
    layout->addWidget(tabWidgetIODevices);
    createTabwidgetIODevices();
}

void StateMachinePage::createTabwidgetIODevices() {

    tabWidgetIODevices->setTabPosition(QTabWidget::West);
    QObject::connect(tabWidgetIODevices, &QTabWidget::currentChanged,
                     this, &StateMachinePage::onChangeIndexTabWidgetIODevices);

    //tabWidgetIODevices->setMinimumSize(500, 500);
    //tabWidgetIODevices->setContentsMargins(10, 50, 10, 25);
    //tabWidgetIODevices->move(5, 110);
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

    //createDefaultPage();
}
void StateMachinePage::createDefaultPage() {
    auto lblStatusArduino1 = new QLabel("Arduino 1");
    auto lblStatusArduino2 = new QLabel("Arduino 2");
    gridLayout->addWidget(lblStatusArduino1, 0, 0, Qt::AlignLeft);
    gridLayout->addWidget(lblStatusArduino2, 0, 1, Qt::AlignLeft);

    auto lblBunker1 = new QLabel("Zand fijn");
    auto lblBunker2 = new QLabel("Zand grof");
    auto lblBunker3 = new QLabel("Grind fijn");

    gridLayout->addWidget(lblBunker1, 1, 0, Qt::AlignLeft);
    gridLayout->addWidget(lblBunker2, 1, 1, Qt::AlignLeft);
    gridLayout->addWidget(lblBunker3, 1, 2, Qt::AlignLeft);

    defaultPage->setLayout(gridLayout);
    tabWidgetIODevices->setCurrentWidget(defaultPage);
}
void StateMachinePage::createDetectionSensorPage() {
    auto lblSensor1 = new QLabel("Weeg cell 1");
    gridLayout->addWidget(lblSensor1, 0, 0, Qt::AlignLeft);
    detectionSensorPage->setLayout(gridLayout);
    tabWidgetIODevices->setCurrentWidget(weightSensorPage);
}

void StateMachinePage::deleteChildrenFromGrid() {
    while (!gridLayout->isEmpty()) {
        auto w = gridLayout->takeAt(0)->widget();
        w->deleteLater();
        printf("deleted child in statemachine tab");
    }
}
void StateMachinePage::onChangeIndexTabWidgetIODevices(int) {

}


