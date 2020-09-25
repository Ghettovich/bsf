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
 * Listen for incoming udp payload from weightstation.
 * After parsing the IODevice it's casted to an WeightSensor.
 * A weight sensor contains a recipe in which we update its components.
 * */
void PayloadServiceTest::parseUpdateRecipeComponents() {
    // ARRANGE
    auto parent = new QObject;
    PayloadService payloadService(parent);

    qRegisterMetaType<Arduino::ARDUINO_STATE>();
    qRegisterMetaType<IODevice*>();

    QSignalSpy spy(&payloadService, SIGNAL(receivedUpdateForWeightSensor(IODevice*, Arduino::ARDUINO_STATE)));
    QVERIFY(spy.isValid());

    QFile jsonFile("resource/updatedRecipePayload.json");

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
        auto iodevice = qvariant_cast<QIODevice*>(arguments.at(0));
        WeightSensor weightSensor = reinterpret_cast<WeightSensor &&>(iodevice);

        auto newState = qvariant_cast<Arduino::ARDUINO_STATE>(arguments.at(1));
        QVERIFY(newState == Arduino::RECIPE_SET);

        QVERIFY(weightSensor.getId() != 0);
        QVERIFY(weightSensor.getRecipe().getId() != 0);
        QVERIFY(!weightSensor.getRecipe().componentList.empty());
    }
}

/*
 * Test is pretty similar as parseUpdateRecipeComponents() but now all targets are met.
 * This is verified by retrieving the recipe from the database and
 * */
void PayloadServiceTest::parseUpdateRecipeComponentsTargetMet() {
    // ARRANGE
    auto parent = new QObject;
    PayloadService payloadService(parent);
    
    RecipeRepository recipeRepository;
    int recipeId = 1;
    Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);

    qRegisterMetaType<Arduino::ARDUINO_STATE>();
    qRegisterMetaType<IODevice*>();

    QSignalSpy spy(&payloadService, SIGNAL(receivedUpdateForWeightSensor(IODevice*, Arduino::ARDUINO_STATE)));
    QVERIFY(spy.isValid());

    QFile jsonFile("resource/recipeCompletedPayload.json");

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
        auto iodevice = qvariant_cast<QIODevice*>(arguments.at(0));
        WeightSensor weightSensor = reinterpret_cast<WeightSensor &&>(iodevice);

        auto newState = qvariant_cast<Arduino::ARDUINO_STATE>(arguments.at(1));
        QVERIFY(newState == Arduino::RECIPE_TARGETS_MET);
        
        recipe.updateComponents(weightSensor.getRecipe().componentList);

        QVERIFY(recipe.isRecipeTargetMet());
    }
}

/*
 * Payload service listens for incoming payloads. On receive it should parse the payload identifying the arduino,
 * state and iodevicelist. Payload is mocked from a json file.
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
 * Emit a payload to a faulty host and check if error signal is properly emitted.
 * */
void PayloadServiceTest::isUdpSocketErrorEmitted() {
    // ARRANGE
    int arduinoId = 2, recipeId = 1;
    const QString host = "asdje9217asd"; // random value for host
    ArduinoRepository arduinoRepository;
    Arduino arduino = arduinoRepository.getArduino(arduinoId);
    RecipeRepository recipeRepository;
    Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);

    QVERIFY(arduino.getId() != 0);
    QVERIFY(recipe.getId() != 0);

    auto parent = new QObject;
    PayloadService payloadService(parent);
    UdpServer udpServer(parent);
    QSignalSpy spy(&payloadService, SIGNAL(receivedError()));
    QVERIFY(spy.isValid());

    // ACT
    payloadService.broadcastRecipe(recipe, arduino.getId(), host, udpServer.getPort()); //

    // ASSERT
    QVERIFY(spy.wait(1000));
    QCOMPARE(spy.count(), 1);
}

/*
 * Set-up a locale udp server and broadcast a datagram (payload) to it.
 * Signals are emitted when connecting is established, making sure our host is able te receive the datagram.
 * Contents of the payload do NOT really matter as long as the output is of type QByteArray.
 * */
void PayloadServiceTest::broadcastRecipePayload() {
    // ARRANGE
    int arduinoId = 2, recipeId = 1;
    const QString host = "127.0.0.1"; // localhost doesn't seem to work ??
    ArduinoRepository arduinoRepository;
    Arduino arduino = arduinoRepository.getArduino(arduinoId);
    RecipeRepository recipeRepository;
    Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);

    QVERIFY(arduino.getId() != 0);
    QVERIFY(recipe.getId() != 0);

    auto parent = new QObject;
    PayloadService payloadService(parent);
    UdpServer udpServer(parent);
    QSignalSpy spy(&udpServer, SIGNAL(receivedPayload(const QByteArray&)));
    QVERIFY(spy.isValid());

    // ACT
    payloadService.broadcastRecipe(recipe, arduino.getId(), host, udpServer.getPort()); //

    QVERIFY(spy.wait(1000));
    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QByteArray actualPayload(arguments.first().toByteArray());

    // ASSERT
    QVERIFY(arguments.first().type() == QVariant::ByteArray);
}

void PayloadServiceTest::cleanupTestCase() {
}

