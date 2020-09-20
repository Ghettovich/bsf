#include "tst_iodeviceservice.h"

DECLARE_TEST_IODEVICESERVICE(IODeviceServiceTest)

void IODeviceServiceTest::initTestCase() {
    qDebug("Called before everything else.");
}

void IODeviceServiceTest::cleanupTestCase() {
    qDebug("Called after myFirstTest and mySecondTest.");
}
