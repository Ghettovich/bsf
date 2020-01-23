#include "statemachinepage.h"
#include <QtWidgets/QLabel>

StateMachinePage::StateMachinePage(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f),
                                                                                gridLayout(new QGridLayout) {
//    createDefaultPage();
//    createDetectionSensorPage();
    //Create toolbox last
    tabWidgetIODevices = new QTabWidget(parent);//(parent);//(parent);
    createTabwidgetIODevices();
    // Set default page
}

void StateMachinePage::createTabwidgetIODevices() {

    tabWidgetIODevices->setTabPosition(QTabWidget::West);
    tabWidgetIODevices->setMinimumSize(500, 500);
    tabWidgetIODevices->setContentsMargins(10, 50, 10, 25);
    tabWidgetIODevices->move(150, 150);
    tabWidgetIODevices->show();

    QObject::connect(tabWidgetIODevices, &QTabWidget::currentChanged,
                     this, &StateMachinePage::onChangeIndexToolboxIODevices);

    //setLayout(gridLayout);

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

}
void StateMachinePage::createDetectionSensorPage() {
    auto lblSensor1 = new QLabel("Weeg cell 1");
    gridLayout->addWidget(lblSensor1, 0, 0, Qt::AlignLeft);
    detectionSensorPage->setLayout(gridLayout);
    tabWidgetIODevices->setCurrentWidget(weightSensorPage);
}
void StateMachinePage::onChangeIndexToolboxIODevices(int index) {
    while (!gridLayout->isEmpty()) {
        auto w = gridLayout->takeAt(0)->widget();
        w->deleteLater();
        printf("deleted child in statemachine tab");
    }

    if (index == 0) {
        printf("creating statemachine default");
        createDefaultPage();
    } else if (index == 1) {
        printf("creating statemachine detect. page");
        createDetectionSensorPage();
    }
}

