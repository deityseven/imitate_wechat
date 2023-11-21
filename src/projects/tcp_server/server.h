#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>
#include <memory>

class TcpServerImpl;

class TcpServer
{
public:
    TcpServer(std::string serverHost, unsigned int serverPort);
    ~TcpServer();

    void listen();
protected:
    void startAccept();

private:
    std::string serverHost;
    unsigned int serverPort;

    TcpServerImpl* impl;
};

#endif // !CONFIG_FILE_H