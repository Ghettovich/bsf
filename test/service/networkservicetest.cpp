#include "networkservicetest.h"
#include <service/networkservice.h>
#include <QtTest/QSignalSpy>
#include <repo/arduinorepo.h>


DECLARE_TEST_NETWORKSERVICE(NetworkServiceTest)


void NetworkServiceTest::initTestCase() {
    ::testing::Environment * const env = ::testing::AddGlobalTestEnvironment(
        httpmock::createMockServerEnvironment<HttpServer>());
    mock_server_env = dynamic_cast<httpmock::TestEnvironment<httpmock::MockServerHolder> *>(env);
}

void NetworkServiceTest::requestFullStatePayload() {
    int arduinoId = 1, initialSpyCount = 0;
    auto parent = new QObject;
    QByteArray payload;
    auto bsfRequestManager = new RequestManager(parent);
    Arduino::ARDUINO_STATE state = Arduino::UNKOWN;
    auto networkService = new NetworkService(parent);

    QSignalSpy spy (bsfRequestManager, SIGNAL(httpCallReady(QByteArray array)));
    initialSpyCount = spy.count();
    QString url = getServeUrl().append("test");

    ArduinoRepository arduinoRepository;
    Arduino arduino = arduinoRepository.getArduino(arduinoId);

    networkService->requestPayload(arduino, arduino.generateQUrl());
    QVERIFY(spy.wait(250));

    QVERIFY(spy.count() != initialSpyCount);
    QVERIFY(payload == "payload test");

//    qRegisterMetaType<Arduino>();
//    qRegisterMetaType<IODevice*>();
//
//    QSignalSpy spy(networkService, SIGNAL(sendArduinoWithNewStates(int, qRegisterMetaType<Arduino>(), const QVector<IODevice *>&)));
//    networkService->requestPayload(reply, arduino.generateQUrl());
//
//
//    printf("\n%s", qUtf8Printable(reply->readAll()));
//
//    QList<QVariant> arguments = spy.takeFirst();
//
//    QVERIFY(arguments.at(0).type() == QVariant::Int);
//    auto newState = qvariant_cast<Arduino::ARDUINO_STATE>(spy.at(1));
//    auto ioDeviceList = qvariant_cast<QVector<IODevice*>>(spy.at(2));
}

void NetworkServiceTest::cleanupTestCase() {

}
