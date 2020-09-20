#include "tst_networkservice.h"
#include <service/networkservice.h>
#include <QtTest/QSignalSpy>
#include <repo/arduinorepo.h>


DECLARE_TEST_NETWORKSERVICE(NetworkServiceTest)


void NetworkServiceTest::initTestCase() {
    ::testing::Environment * const env = ::testing::AddGlobalTestEnvironment(
        httpmock::createMockServerEnvironment<HttpServer>(8080));
    mock_server_env = dynamic_cast<httpmock::TestEnvironment<httpmock::MockServerHolder> *>(env);
}



void NetworkServiceTest::requestFullStatePayload() {
    int arduinoId = 1;
    auto parent = new QObject;
    std::string location = "payload";
    Arduino::ARDUINO_STATE state = Arduino::UNKOWN;
    auto networkService = new NetworkService(parent);

    qRegisterMetaType<Arduino::ARDUINO_STATE>();
    qRegisterMetaType<QVector<IODevice*>>();

    QSignalSpy spy (networkService, SIGNAL(sendArduinoWithNewStates(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&)));
    QVERIFY(spy.isValid());

    ArduinoRepository arduinoRepository;
    Arduino arduino = arduinoRepository.getArduino(arduinoId);

    QString url = QString::fromStdString(getServeUrl().append(location));
    networkService->requestPayload(arduino, url);

    QVERIFY(spy.wait(1000));

    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).type() == QVariant::Int);

    auto newState = qvariant_cast<Arduino::ARDUINO_STATE>(arguments.at(1));
    QVERIFY(newState != state);

    auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(2));
    QVERIFY(!iodeviceList.isEmpty());
}

void NetworkServiceTest::cleanupTestCase() {

}
