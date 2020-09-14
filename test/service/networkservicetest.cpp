#include "networkservicetest.h"
#include <service/networkservice.h>
#include <QtTest/QSignalSpy>
#include <QtNetwork/QNetworkReply>
#include <repo/arduinorepo.h>
//#include <httpmockserver/mock_server.h>
//#include <httpmockserver/test_environment.h>

//DECLARE_TEST_NETWORKSERVICE(NetworkServiceTest)

void NetworkServiceTest::initTestCase() {
}

void NetworkServiceTest::requestFullStatePayload() {
    int arduinoId = 1;
    QString connectionString = "data/bsfTest.db";
    Arduino::ARDUINO_STATE state = Arduino::UNKOWN;
    auto parent = new QObject;
    auto networkService = new NetworkService(parent);
    QNetworkReply *reply = nullptr;

    ArduinoRepository arduinoRepository(connectionString);
    Arduino arduino = arduinoRepository.getArduino(arduinoId);

    qRegisterMetaType<Arduino>();
    qRegisterMetaType<IODevice*>();

    QSignalSpy spy(networkService, SIGNAL(sendArduinoWithNewStates(int, qRegisterMetaType<Arduino>(), const QVector<IODevice *>&)));
    networkService->requestPayload(*reply, arduino.generateQUrl());


    printf("\n%s", qUtf8Printable(reply->readAll()));

    QList<QVariant> arguments = spy.takeFirst();

    QVERIFY(arguments.at(0).type() == QVariant::Int);
    auto newState = qvariant_cast<Arduino::ARDUINO_STATE>(spy.at(1));
    auto ioDeviceList = qvariant_cast<QVector<IODevice*>>(spy.at(2));
}

void NetworkServiceTest::cleanupTestCase() {

}
