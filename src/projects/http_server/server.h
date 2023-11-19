#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <string>

namespace httplib
{
    class Server;
}

class HttpServer
{
public:
    HttpServer(std::string serverHost, unsigned int serverPort);
    ~HttpServer();

    void run();

private:
    std::string serverHost;
    unsigned int serverPort;
    httplib::Server* server;
};

#endif // !CONFIG_FILE_H