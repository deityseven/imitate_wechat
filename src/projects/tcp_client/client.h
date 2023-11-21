#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>

class TcpClientImpl;

class TcpClient
{
public:
    TcpClient(std::string serverHost, unsigned int serverPort);
    ~TcpClient();

    bool connect();

    void sendMessage(const std::string data);

private:
    TcpClientImpl* impl;
};

#endif // !CONFIG_FILE_H