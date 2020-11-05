#include "tst_requestmanager.h"
#include <QtTest/QSignalSpy>
#include <service/requestmanager/requestmanager.h>

//DECLARE_TEST_REQUESTMANAGER(RequestManagerTest)

void RequestManagerTest::initTestCase() {
    ::testing::Environment * const env = ::testing::AddGlobalTestEnvironment(
            httpmock::createMockServerEnvironment<HttpServer>());
    mock_server_env = dynamic_cast<httpmock::TestEnvironment<httpmock::MockServerHolder> *>(env);
}

/*
 * Check if the body contents (payload) of the HTTP request matches is as expected.
 * */
void RequestManagerTest::isHttpCallReadyEmitted() {
    // ARRANGE
    auto parent = new QObject;
    QNetworkRequest request;
    QByteArray expectedPayload("payload test");
    std::string location = "test"; // returns explicit error status code with plain body

    RequestManager requestManager(parent);
    QSignalSpy spy(&requestManager, SIGNAL(httpCallReady(QByteArray)));
    QVERIFY(spy.isValid());

    const QString url = QString::fromStdString(getServeUrl().append(location));
    request.setUrl(url);

    // ACT
    requestManager.sendGetRequest(request);

    QVERIFY(spy.wait(1000));
    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QByteArray payload(arguments.first().toByteArray());

    // ASSERT
    QCOMPARE(payload, expectedPayload);
}

/*
 * Tests if the httpError signal is triggered with a faulty response.
 * */
void RequestManagerTest::isHttpErrorEmitted() {
    // ARRANGE
    auto parent = new QObject;
    QNetworkRequest request;
    auto expectedError = QNetworkReply::NetworkError::InternalServerError;
    std::string location = "error"; // returns explicit error status code with plain body

    RequestManager requestManager(parent);

    qRegisterMetaType<QNetworkReply::NetworkError>();
    QSignalSpy spy (&requestManager, SIGNAL(httpError(QNetworkReply::NetworkError)));
    QVERIFY(spy.isValid());

    const QString url = QString::fromStdString(getServeUrl().append(location));
    request.setUrl(url);

    // ACT
    requestManager.sendGetRequest(request);

    QVERIFY(spy.wait(1000));
    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    auto errorCode = qvariant_cast<QNetworkReply::NetworkError>(arguments.at(0));

    // ASSERT
    QCOMPARE(errorCode, expectedError);
}

void RequestManagerTest::cleanupTestCase() {

}
