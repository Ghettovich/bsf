#ifndef BSF_HTTPSERVER_H
#define BSF_HTTPSERVER_H

#include <QtCore/QString>
#include <gtest/gtest.h>
#include <string>
#include <httpmockserver/mock_server.h>
#include <httpmockserver/test_environment.h>


/// Port number server is tried to listen on
/// Number is being incremented while free port has not been found.
static const int server_port = 8080;

/// Server started in the main().
static httpmock::TestEnvironment<httpmock::MockServerHolder>* mock_server_env = nullptr;

static QString getServeUrl() {
    assert(nullptr != mock_server_env);
    const int port = mock_server_env->getMock()->getPort();
    QString url;
    //std::ostringstream url;
    url.append("http://localhost:").append(port).append("/");
    return url;
}


class HttpServer : public httpmock::MockServer {
public:
    explicit HttpServer(int port = 9200);

private:
    virtual Response processHeaderOutTest();
    Response responseHandler(
            const std::string &url,
            const std::string &method,
            const std::string &data,
            const std::vector<UrlArg> &urlArguments,
            const std::vector<Header> &headers) override;

    bool matchesPrefix(const std::string &url, const std::string &str) const;

};


#endif //BSF_HTTPSERVER_H
