#include "tst_networkservice.h"
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

    Arduino::ARDUINO_STATE state = Arduino::UNKOWN;
    auto networkService = new NetworkService(parent);

    auto requestManager = new RequestManager(networkService);

    qRegisterMetaType<Arduino::ARDUINO_STATE>();
    qRegisterMetaType<QVector<IODevice*>>();

    QSignalSpy spy (networkService, SIGNAL(sendArduinoWithNewStates(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&)));
    QVERIFY(spy.isValid());

    initialSpyCount = spy.count();
    QString url = getServeUrl().append("test");

    ArduinoRepository arduinoRepository;
    Arduino arduino = arduinoRepository.getArduino(arduinoId);

    networkService->requestPayload(arduino,QString("http://localhost:8080/payload"));

    QVERIFY(spy.wait(1000));


    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).type() == QVariant::Int);
//
//    auto newState = qvariant_cast<Arduino::ARDUINO_STATE>(spy.at(0).at(1));
//    QVERIFY(newState == Arduino::READY);
//
//    QVector<IODevice *> list = qvariant_cast<QVector<IODevice*>>(spy.at(0).at(2));
//    QVERIFY(list.count() == 0);



//
//    QVERIFY(arguments.at(0).type() == QVariant::Int);
//    auto newState = qvariant_cast<Arduino::ARDUINO_STATE>(spy.at(1));
//    auto ioDeviceList = qvariant_cast<QVector<IODevice*>>(spy.at(2));
}

void NetworkServiceTest::cleanupTestCase() {

}
