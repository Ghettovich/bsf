#include "iodeviceservicetest.h"
#include <QtWidgets/QHBoxLayout>

void IODeviceServiceTest::initTestCase() {
    qDebug("Called before everything else.");
}

void IODeviceServiceTest::myFirstTest() {
    auto layout = new QHBoxLayout;
    //auto ioDeviceService = new IODeviceService(this, connectionString);
//
//    ioDeviceService->createArduinoDeviceWidgetList(layout);

    QVERIFY(!layout->isEmpty());
}

void IODeviceServiceTest::cleanupTestCase() {
    qDebug("Called after myFirstTest and mySecondTest.");
}
