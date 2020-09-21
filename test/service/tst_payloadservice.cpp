#include "tst_payloadservice.h"
#include <QtTest/QSignalSpy>
#include <service/payloadservice.h>
#include <service/socketmanager/udpserver.h>

DECLARE_TEST_PAYLOADSERVICE(PayloadServiceTest)

void PayloadServiceTest::initTestCase() {
}

/*
 * Payload service listens for incoming payloads. On receive it should parse the payload identifying the arduino, state
 * and iodevicelist. Payload is mocked from a json file.
 * */
void PayloadServiceTest::parsePayloadOnIncomingUdpPackets() {
    // ARRANGE
    int socketManagerPort = 6677; // ToDo: Should really replace with confiig file variable / macro
    auto parent = new QObject;
    PayloadService payloadService(parent);
    Arduino::ARDUINO_STATE state = Arduino::UNKOWN;
    QSignalSpy spy(&payloadService, SIGNAL(
            receivedIODevicesWithNewState(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&)));
    QVERIFY(spy.isValid());

    QFile jsonFile("resource/payload.json");

    if(jsonFile.open(QIODevice::ReadOnly)) {
        UdpServer udpServer(parent);
        QHostAddress hostAddress(QHostAddress::LocalHost);
        QByteArray payload(jsonFile.readAll());

        // ACT
        QNetworkDatagram datagram(payload, hostAddress, socketManagerPort);
        udpServer.broadcastDatagram(datagram);

        QVERIFY(spy.wait(1000));
        QCOMPARE(spy.count(), 1);

        // ASSERT
        QList<QVariant> arguments = spy.takeFirst();
        QVERIFY(arguments.at(0).type() == QVariant::Int);

        auto newState = qvariant_cast<Arduino::ARDUINO_STATE>(arguments.at(1));
        QVERIFY(newState != state);

        auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(2));
        QVERIFY(!iodeviceList.isEmpty());
    } else {
        QVERIFY2(false, "Could not read JSON file.");
    }
}

void PayloadServiceTest::cleanupTestCase() {
}

