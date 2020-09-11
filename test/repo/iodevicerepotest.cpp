#include <repo/iodevicerepo.h>
#include "iodevicerepotest.h"
#include <QtTest/QtTest>

DECLARE_TEST_IODEVICE_REPO(IODeviceRepoTest)

void IODeviceRepoTest::initTestCase() {
}

void IODeviceRepoTest::isIODeviceListNotEmpty() {
    QString connectionString = "data/bsfTest.db";
    int arduinoId = 1;
    IODeviceRepository ioDeviceRepository(connectionString);
    QVector<IODeviceType> ioDeviceTypeList;

    ioDeviceTypeList = ioDeviceRepository.getArduinoIODeviceTypes(arduinoId);

    QVERIFY(!ioDeviceTypeList.isEmpty());
}

void IODeviceRepoTest::isIODeviceTypeFound() {
    QString connectionString = "data/bsfTest.db";
    int ioDeviceTypeId = 1;
    IODeviceRepository ioDeviceRepository(connectionString);

    IODeviceType ioDeviceType = ioDeviceRepository.getIODeviceType(ioDeviceTypeId);

    QVERIFY(ioDeviceType.getId() != 0);
}


void IODeviceRepoTest::isIODeviceListFromArduinoEmpty() {
    QString connectionString = "data/bsfTest.db";
    int ioDeviceTypeId = 1, arduinoId = 1;
    IODeviceRepository ioDeviceRepository(connectionString);

    QVector<IODevice *> ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduinoId, ioDeviceTypeId, IODeviceType::RELAY);

    QVERIFY(!ioDeviceList.empty());

    ioDeviceTypeId = 2;
    ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduinoId, ioDeviceTypeId, IODeviceType::RELAY);

    QVERIFY(!ioDeviceList.empty());
}

void IODeviceRepoTest::cleanUpTestCase() {

}
