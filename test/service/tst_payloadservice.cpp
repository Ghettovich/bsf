#include "tst_payloadservice.h"
#include <QtTest/QSignalSpy>
#include <service/payloadservice.h>
#include <service/socketmanager/udpserver.h>
#include <repo/arduinorepo.h>
#include <repo/reciperepo.h>

DECLARE_TEST_PAYLOADSERVICE(PayloadServiceTest)

void PayloadServiceTest::initTestCase() {
}

/*
 * Payload service listens for incoming payloads. On receive it should parse the payload identifying the arduino, state
 * and iodevicelist. Payload is mocked from a json file.
 * */
void PayloadServiceTest::parsePayloadOnIncomingUdpPackets() {
    // ARRANGE
    auto parent = new QObject;
    PayloadService payloadService(parent);
    Arduino::ARDUINO_STATE state = Arduino::UNKOWN;
    QSignalSpy spy(&payloadService, SIGNAL(
            receivedIODevicesWithNewState(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&)));
    QVERIFY(spy.isValid());

    QFile jsonFile("resource/payload.json");

    if (jsonFile.open(QIODevice::ReadOnly)) {
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

/*
 * Set-up a locale udp server and broadcast a datagram (payload) to it.
 * Contents of the payload do matter and have to be exactly the same.
 * */
void PayloadServiceTest::broadcastRecipePayload() {
    // ARRANGE
    int arduinoId = 2;
    const QString host = "localhost";
    auto parent = new QObject;
    PayloadService payloadService(parent);
    ArduinoRepository arduinoRepository;
    Arduino arduino = arduinoRepository.getArduino(arduinoId);
    QFile jsonFile("resource/recipePayload.json");
    

    if (jsonFile.open(QIODevice::ReadOnly)) {
        UdpServer udpServer(parent);
        QSignalSpy spy(&udpServer, SIGNAL(receivedPayload(const QByteArray&)));
        QVERIFY(spy.isValid());
        
        RecipeRepository recipeRepository;
        int recipeId = 1;
        Recipe recipe = recipeRepository.getRecipe(recipeId);

        // ACT
        payloadService.broadcastRecipe(recipe, arduino.getId(), "localhost", udpServer.getPort());

        // VERIFY
        QVERIFY(spy.wait(1000));
        QCOMPARE(spy.count(), 1);
        
    } else {
        QVERIFY2(false, "Unable to find recipe payload file.");
    }

}

void PayloadServiceTest::cleanupTestCase() {
}

