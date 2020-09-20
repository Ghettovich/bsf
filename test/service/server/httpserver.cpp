#include "httpserver.h"
//#include <QtTest/QtTest>
//#include <QtTest/QSignalSpy>
//#include "requestmanager.h"

HttpServer::HttpServer(int port) : MockServer(port) {
}

httpmock::MockServer::Response
HttpServer::responseHandler(const std::string &url, const std::string &method, const std::string &data,
                            const std::vector<UrlArg> &urlArguments, const std::vector<Header> &headers) {
    if (method == "POST" && matchesPrefix(url, "/example")) {
        // Do something and return response
        return Response(500, "Fake HTTP response");
    }
    if (method == "GET" && matchesPrefix(url, "/payload")) {
        // Do something and return response
        return Response(200, "{}");
    }
    if (method == "GET" && matchesPrefix(url, "/test")) {
        // Do something and return response
        return Response(200, "payload test");
    }


    // Return "URI not found" for the undefined methods
    return Response(404, "Not Found");
}

/// Return true if \p url starts with \p str.
bool HttpServer::matchesPrefix(const std::string &url, const std::string &str) const {
    return url.substr(0, str.size()) == str;
}


/// Process /header_out request
httpmock::MockServer::Response
HttpServer::processHeaderOutTest() {
    return Response(201, "{}")
            .addHeader({"Content-type", "application/json"});
}

TEST(MyTest, dummyTest) {
//    auto parent = new QObject;
//    QNetworkReply *reply = nullptr;
//    auto bsfRequestManager = new RequestManager(parent);
//
//    QSignalSpy spy (bsfRequestManager, SIGNAL(httpCallReady()));
//    QString url = getServeUrl().append("test");
//
//    bsfRequestManager->sendRequest(url, reply);
//
//    ASSERT_EQ(spy.count(), 0);
//
//    QVERIFY(spy.wait(1000));
//
//    ASSERT_EQ(spy.count(), 1); // make sure the signal was emitted exactly one time
//
//    ASSERT_EQ(reply->readAll(), "payload test");
}

TEST(Server, launchFailure) {
    ASSERT_NE(nullptr, mock_server_env);
    const int port = mock_server_env->getMock()->getPort();

    // try to start the server on already used port (with single try)
    EXPECT_THROW({
                     httpmock::createMockServerEnvironment<HttpServer>(port, 1);
                 }, std::runtime_error);
}


int main(int argc, char *argv[]) {
    //QApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    // startup the server for the tests
    ::testing::Environment * const env = ::testing::AddGlobalTestEnvironment(
            httpmock::createMockServerEnvironment<HttpServer>(server_port));
    // set global env pointer
    mock_server_env = dynamic_cast<httpmock::TestEnvironment<httpmock::MockServerHolder> *>(env);
    return RUN_ALL_TESTS();
}
