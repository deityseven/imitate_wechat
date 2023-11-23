#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>
#include <signalslot/Signal.hpp>

class TcpClientImpl;

class TcpClient
{
public:
    TcpClient(std::string serverHost, unsigned int serverPort);
    ~TcpClient();

    bool connect();

    bool sendMessage(const std::string data);

    void run();
signals:
    Gallant::Signal1<std::string> recvMessageSignal;

private:
    void recvMessage(std::string data);

private:
    TcpClientImpl* impl;
};

#endif // !CONFIG_FILE_H