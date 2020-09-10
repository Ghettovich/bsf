#include "iodeviceservicetest.h"
#include <QtWidgets/QHBoxLayout>
#include <service/iodeviceservice.h>
#include <factory/iodeviceformfactory.h>

DECLARE_TEST_IODEVICESERVICE(IODeviceServiceTest)

void IODeviceServiceTest::initTestCase() {
    qDebug("Called before everything else.");
}

void IODeviceServiceTest::isArduinoDeviceWidgetListOnLayout() {
    auto layout = new QHBoxLayout;
    auto parent = new QObject;
    QString connectionString = "data/bsfTest.db";

    IODeviceService ioDeviceService(parent, connectionString);
    ioDeviceService.createArduinoDeviceWidgetList(layout);

    QVERIFY(!layout->isEmpty());
}

void IODeviceServiceTest::isDeviceActionFormCreated() {
    QString connectionString = "data/bsfTest.db";
    auto parent = new QWidget;
    auto devForm = IODeviceFormFactory::createDeviceActiomForm(parent);

    IODeviceService ioDeviceService(parent, connectionString);
    ioDeviceService.createDeviceActionForm(devForm);

    QVERIFY(devForm->selectedArduino().getId() != 0);
}

void IODeviceServiceTest::isIODeviceLayoutPopulated() {
    QString connectionString = "data/bsfTest.db";
    auto parent = new QWidget;
    auto devForm = IODeviceFormFactory::createDeviceActiomForm(parent);

    IODeviceService ioDeviceService(parent, connectionString);
    ioDeviceService.createDeviceActionForm(devForm);

    auto ioDevForm = IODeviceFormFactory::createIODeviceForm(parent);
    auto arduino = devForm->selectedArduino();

    ioDeviceService.createIODeviceForm(ioDevForm, arduino);

    QVERIFY(ioDevForm->isIODeviceListEmpty() == false);
}

void IODeviceServiceTest::cleanupTestCase() {
    qDebug("Called after myFirstTest and mySecondTest.");
}
