#include "iodeviceservicetest.h"
#include <QtWidgets/QHBoxLayout>
//#include <service/iodeviceservice.h>

void IODeviceServiceTest::initTestCase() {
    qDebug("Called before everything else.");
}

void IODeviceServiceTest::myFirstTest() {
    auto layout = new QHBoxLayout;
    auto parent = new QObject;
    QString connectionString = "data/bsfTest.db";

    //IODeviceService ioDeviceService(parent, connectionString);

//
//    ioDeviceService->createArduinoDeviceWidgetList(layout);

    QVERIFY(!layout->isEmpty());
}

void IODeviceServiceTest::cleanupTestCase() {
    qDebug("Called after myFirstTest and mySecondTest.");
}
