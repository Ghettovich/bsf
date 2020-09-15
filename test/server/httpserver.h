#ifndef BSF_HTTPSERVER_H
#define BSF_HTTPSERVER_H

#include <gtest/gtest.h>
#include <string>
#include <httpmockserver/mock_server.h>
#include <httpmockserver/test_environment.h>


class HttpServer : public httpmock::MockServer {
public:
    explicit HttpServer(int port = 9200);

private:
    virtual Response processHeaderOutTest();
    virtual Response responseHandler(
            const std::string &url,
            const std::string &method,
            const std::string &data,
            const std::vector<UrlArg> &urlArguments,
            const std::vector<Header> &headers);

    bool matchesPrefix(const std::string &url, const std::string &str) const;

};


#endif //BSF_HTTPSERVER_H
