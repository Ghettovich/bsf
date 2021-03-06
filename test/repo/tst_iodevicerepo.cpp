#include <repo/iodevicerepo.h>
#include "tst_iodevicerepo.h"
#include <QtTest/QtTest>

DECLARE_TEST_IODEVICE_REPO(IODeviceRepoTest)

void IODeviceRepoTest::initTestCase() {
}

/*
 * Tests is the iodevice list is not empty.
 * */
void IODeviceRepoTest::isIODeviceListNotEmpty() {
    // ARRANGE
    int arduinoId = 1;
    const QString testConnection = "/home/mrfunkyman/Documents/databases/bsf/test/bsf.db";
    IODeviceRepository ioDeviceRepository(testConnection);
    QVector<IODeviceType> ioDeviceTypeList;

    // ACT
    ioDeviceTypeList = ioDeviceRepository.getArduinoIODeviceTypes(arduinoId);

    // ASSERT
    QVERIFY(!ioDeviceTypeList.isEmpty());
}

/*
 * Checks if the io device type with id N is found
 * */
void IODeviceRepoTest::isIODeviceTypeFound() {
    // ARRANGE
    int ioDeviceTypeId = 1;
    IODeviceRepository ioDeviceRepository;

    // ACT
    IODeviceType ioDeviceType = ioDeviceRepository.getIODeviceType(ioDeviceTypeId);

    // ASSERT
    QVERIFY(ioDeviceType.getId() != 0);
}

/*
 * Checks if the relay list is not empty.
 * */
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

/*
 * Checks if the dection sensor list is not empty.
 * */
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

/*
 * Checks if the weight sensor list is not empty. Only arduino with id 2 has loadcells.
 * */
void IODeviceRepoTest::isWeightSensorListEmpty() {
    // ARRANGE
    int ioDeviceTypeId = 1, arduinoId = 2;
    IODeviceRepository ioDeviceRepository;

    // ACT
    QVector<IODevice *> ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(
            arduinoId, ioDeviceTypeId, IODeviceType::WEIGHTSENSOR);

    // ASSERT
    QVERIFY(!ioDeviceList.empty());
}

void IODeviceRepoTest::cleanUpTestCase() {

}
