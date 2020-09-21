#include <domain/arduino.h>
#include <parser//transformpayload.h>
#include "tst_transformpayload.h"

DECLARE_TEST_TRANSFORMPAYLOAD(TransformPayloadTest)

void TransformPayloadTest::initTestCase() {
}

/*
 * Load up the full payload state from a JSON file and check if it succesfully parsed.
 * */
void TransformPayloadTest::isArduinoUpdatedWithStateAndIODeviceList() {
    // ARRANGE
    int arduinoId = 0;
    Arduino::ARDUINO_STATE state = Arduino::UNKOWN;
    QVector<IODevice *> ioDeviceList;
    QFile jsonFile("resource/payload.json");

    // ACT
    jsonFile.open(QIODevice::ReadOnly);
    TransformPayload::updateArduinoWithPayload(arduinoId, state, ioDeviceList, jsonFile.readAll());

    // ASSERT
    QVERIFY(arduinoId != 0);
    QVERIFY(state != Arduino::UNKOWN);
    QVERIFY(!ioDeviceList.isEmpty());
}

void TransformPayloadTest::cleanupTestCase() {
}
