#include <QtCore/QFile>
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
        QFile jsonFile("resource/payload.json");

        // Do something and return response
        if(jsonFile.open(QIODevice::ReadOnly)) {
            std::string payload = jsonFile.readAll().toStdString();

            return Response(200, payload)
                    .addHeader({"Content-type", "application/json"});
        } else {
            return Response(500, "Unable to load payload.");
        }
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
