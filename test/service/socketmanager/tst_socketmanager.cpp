#include "tst_socketmanager.h"
#include <QtTest/QSignalSpy>
#include <service/socketmanager/udpserver.h>
#include <service/socketmanager/socketmanager.h>

DECLARE_TEST_SOCKETMANAGER(SocketManagerTest)

void SocketManagerTest::initTestCase() {
}

/*
 * Tests if payload is received at UDP server.
 * Signal receivePayload is triggered and it's the only thing checked for.
 * Contents of payload do not matter.
 * */
void SocketManagerTest::connectoToHost() {
    // ARRANGE
    auto parent = new QObject();
    UdpServer udpServer(parent);
    SocketManager socketManager(parent);

    QSignalSpy spy(&udpServer, SIGNAL(receivedPayload(const QByteArray&)));
    QVERIFY(spy.isValid());

    const QByteArray payload("I am a train.");
    QNetworkDatagram datagram(payload, QHostAddress::LocalHost, udpServer.getPort());

    // ACT
    socketManager.broadcastDatagram(datagram);

    QVERIFY(spy.wait(1000));
    QCOMPARE(spy.count(), 1);
}


/*
 * Broadcast a JSON payload from a file to local udp server.
 * */
void SocketManagerTest::broadcastRecipePayload() {
    // ARRANGE
    auto parent = new QObject();
    UdpServer udpServer(parent);
    SocketManager socketManager(parent);
    QFile jsonFile("resource/recipePayload.json");

    if (jsonFile.open(QIODevice::ReadOnly)) {

        QSignalSpy spy(&udpServer, SIGNAL(receivedPayload(const QByteArray&)));
        QVERIFY(spy.isValid());

        QByteArray payload(jsonFile.readAll());
        QNetworkDatagram datagram(payload, QHostAddress::LocalHost, udpServer.getPort());

        // ACT
        udpServer.broadcastDatagram(datagram);
        QVERIFY(spy.wait(1000));
        QCOMPARE(spy.count(), 1);

        QList<QVariant> arguments = spy.takeFirst();
        QByteArray actualPayload(arguments.first().toByteArray());

        // ASSERT
        QCOMPARE(actualPayload, payload);
    }
}

/*
 * Set-up a locale udp server and broadcast a datagram (payload) to it.
 * Contents of the payload do matter and have to be exactly the same.
 * */
void SocketManagerTest::receivePayload() {
    // ARRANGE
    auto parent = new QObject;
    SocketManager socketManager(parent);
    QSignalSpy spy(&socketManager, SIGNAL(receivedPayload(const QByteArray&)));
    QVERIFY(spy.isValid());

    auto udpServer = new UdpServer(parent);
    QByteArray payload("I am a train.");
    QHostAddress hostAddress("localhost");
    QNetworkDatagram datagram(payload, hostAddress, socketManager.getDefaultPort());

    // ACT
    udpServer->broadcastDatagram(datagram);

    QVERIFY(spy.wait(1000));
    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QByteArray actualPayload(arguments.first().toByteArray());

    // ASSERT
    QCOMPARE(actualPayload, payload);
}

void SocketManagerTest::cleanupTestCase() {

}
