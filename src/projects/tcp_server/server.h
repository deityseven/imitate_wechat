#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>

class TcpServer
{
public:
    TcpServer(std::string serverHost, unsigned int serverPort);
    ~TcpServer();

    void listen();

private:
    std::string serverHost;
    unsigned int serverPort;
};

#endif // !CONFIG_FILE_H