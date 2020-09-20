#include <repo/iodevicerepo.h>
#include "tst_iodevicerepo.h"
#include <QtTest/QtTest>

DECLARE_TEST_IODEVICE_REPO(IODeviceRepoTest)

void IODeviceRepoTest::initTestCase() {
}

void IODeviceRepoTest::isIODeviceListNotEmpty() {
    // ARRANGE
    int arduinoId = 1;
    IODeviceRepository ioDeviceRepository;
    QVector<IODeviceType> ioDeviceTypeList;

    // ACT
    ioDeviceTypeList = ioDeviceRepository.getArduinoIODeviceTypes(arduinoId);

    // ASSERT
    QVERIFY(!ioDeviceTypeList.isEmpty());
}

void IODeviceRepoTest::isIODeviceTypeFound() {
    // ARRANGE
    int ioDeviceTypeId = 1;
    IODeviceRepository ioDeviceRepository;

    // ACT
    IODeviceType ioDeviceType = ioDeviceRepository.getIODeviceType(ioDeviceTypeId);

    // ASSERT
    QVERIFY(ioDeviceType.getId() != 0);
}


void IODeviceRepoTest::isRelayListFromArduinoEmpty() {
    // ARRANGE
    int ioDeviceTypeId = 3, arduinoId = 1;
    IODeviceRepository ioDeviceRepository;

    // ACT
    QVector<IODevice *> ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(
            arduinoId, ioDeviceTypeId, IODeviceType::RELAY);

    // ASSERT
    QVERIFY(!ioDeviceList.empty());
}

void IODeviceRepoTest::isDetectionSensorListEmpty() {
    // ARRANGE
    int ioDeviceTypeId = 2, arduinoId = 1;
    IODeviceRepository ioDeviceRepository;

    // ACT
    QVector<IODevice *> ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(
            arduinoId, ioDeviceTypeId, IODeviceType::DETECTIONSENSOR);

    // ASSERT
    QVERIFY(!ioDeviceList.empty());
}

void IODeviceRepoTest::isWeightSensorListEmpty() {
    // ARRANGE
    int ioDeviceTypeId = 1, arduinoId = 1;
    IODeviceRepository ioDeviceRepository;

    // ACT
    QVector<IODevice *> ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(
            arduinoId, ioDeviceTypeId, IODeviceType::WEIGHTSENSOR);

    // ASSERT
    QVERIFY(!ioDeviceList.empty());
}

void IODeviceRepoTest::cleanUpTestCase() {

}
