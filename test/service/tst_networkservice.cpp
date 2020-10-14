#include "tst_networkservice.h"
#include <service/networkservice.h>
#include <QtTest/QSignalSpy>
#include <repo/arduinorepo.h>
#include <repo/reciperepo.h>

DECLARE_TEST_NETWORKSERVICE(NetworkServiceTest)

void NetworkServiceTest::initTestCase() {
    ::testing::Environment * const env = ::testing::AddGlobalTestEnvironment(
        httpmock::createMockServerEnvironment<HttpServer>());
    mock_server_env = dynamic_cast<httpmock::TestEnvironment<httpmock::MockServerHolder> *>(env);
}

/*
 * Since network service holds a TCP server already there is no need to mock one. IP address is 
 * set to localhost so that the request is send to the local server. There is no
 * actual JSON payload but we only care about the valid tcp connection. Once established the assumption
 * is made that data safely be transmitted. 
 */
void NetworkServiceTest::requestFullStatePayload() {
    // ARRANGE
    int arduinoId = 1;
    auto parent = new QObject;
    auto networkService = new NetworkService(parent);

    QSignalSpy spy(networkService, SIGNAL(failedToParseJson()));
    QVERIFY(spy.isValid());

    ArduinoRepository arduinoRepository;
    Arduino arduino = arduinoRepository.getArduino(arduinoId);

    // ACT
    arduino.setIpAddress("127.0.0.1");
    networkService->requestPayload(arduino);

    // ASSERT
    QVERIFY(spy.wait(1000));
    QCOMPARE(spy.count(), 1);
}

/*** !! Doesn't work as expected D: !!
 *
 * Again we make use of the local tcp server that comes with network service. Parse will still fail since when
 * sending the recipe over tcp there is no state attached so it will still fail to emit parsedJson.
 */
//void NetworkServiceTest::setRecipeForWeightStation() {
//    // ARRANGE
//    int arduinoId = 2, recipeId = 1;
//    auto parent = new QObject;
//    auto networkService = new NetworkService(parent);
//    RecipeRepository recipeRepository;
//    Recipe recipe = recipeRepository.getRecipe(recipeId);
//
//    ArduinoRepository arduinoRepository;
//    Arduino arduino = arduinoRepository.getArduino(arduinoId);
//
//    auto localTcpServer = new LocalTcpServer;
//
//    QSignalSpy spy(localTcpServer, SIGNAL(receivedSocketData(const QByteArray &)));
//    QVERIFY(spy.isValid());
//
//    // ACT
//    arduino.setIpAddress("127.0.0.1");
//    networkService->setRecipeForWeightstation(arduino, recipe);
//
//    // ASSERT
//    QVERIFY(spy.wait(1000));
//    QCOMPARE(spy.count(), 1);
//}

/*
 * Tests wether the mocked payload was properly parsed into domain items.
 * Uses the mocked webserver to send a HTTP request to.
 * */
//void NetworkServiceTest::requestFullStatePayload() {
//    // ARRANGE
//    int arduinoId = 1;
//    auto parent = new QObject;
//    std::string location = "payload";
//    Arduino::ARDUINO_STATE state = Arduino::UNKOWN;
//    auto networkService = new NetworkService(parent);
//
//    qRegisterMetaType<Arduino::ARDUINO_STATE>();
//    qRegisterMetaType<QVector<IODevice*>>();
//
//    QSignalSpy spy (networkService, SIGNAL(sendArduinoWithNewStates(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&)));
//    QVERIFY(spy.isValid());
//
//    ArduinoRepository arduinoRepository;
//    Arduino arduino = arduinoRepository.getArduino(arduinoId);
//
//    QString url = QString::fromStdString(getServeUrl().append(location));
//
//    // ACT
//    networkService->requestPayload(arduino, url);
//
//    QVERIFY(spy.wait(1000));
//    QCOMPARE(spy.count(), 1);
//
//    // ASSERT
//    QList<QVariant> arguments = spy.takeFirst();
//    QVERIFY(arguments.at(0).type() == QVariant::Int);
//
//    auto newState = qvariant_cast<Arduino::ARDUINO_STATE>(arguments.at(1));
//    QVERIFY(newState != state);
//
//    auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(2));
//    QVERIFY(!iodeviceList.isEmpty());
//}

void NetworkServiceTest::cleanupTestCase() {

}

