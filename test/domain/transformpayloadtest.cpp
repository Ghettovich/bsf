#include <domain/arduino.h>
#include <domain/transformpayload.h>
#include "transformpayloadtest.h"

DECLARE_TEST_TRANSFORMPAYLOAD(TransformPayloadTest)

void TransformPayloadTest::initTestCase() {
}

void TransformPayloadTest::isArduinoUpdatedWithStateAndIODeviceList() {
    int arduinoId = 0;
    Arduino::ARDUINO_STATE state = Arduino::UNKOWN;
    QVector<IODevice *> ioDeviceList;
    QFile jsonFile("resource/payload.json");

    jsonFile.open(QIODevice::ReadOnly);
    TransformPayload::updateArduinoWithPayload(arduinoId, state, ioDeviceList, jsonFile.readAll());

    QVERIFY(arduinoId != 0);
    QVERIFY(state != Arduino::UNKOWN);
    QVERIFY(!ioDeviceList.isEmpty());
}

void TransformPayloadTest::cleanupTestCase() {
}
