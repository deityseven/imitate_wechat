#include "client.h"

#include <asio.hpp>
#include <spdlog/spdlog.h>

class TcpClientImpl
{
public:
    TcpClientImpl(std::string serverHost, unsigned int serverPort)
        :socketObject(io_context), serverHost(serverHost), serverPort(serverPort)
    {
        spdlog::info("serverHost: {} port: {}", serverHost, serverPort);
    }

    bool connect()
    {
        socketObject.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(this->serverHost), this->serverPort));
        return true;
    }

    void sendMessage(const std::string data)
    {
        this->socketObject.send(asio::buffer(data));
        this->socketObject.shutdown();
    }

private:
    std::string serverHost;
    unsigned int serverPort;
    asio::io_context io_context;
    asio::ip::tcp::socket socketObject;
};


TcpClient::TcpClient(std::string serverHost, unsigned int serverPort)
    :impl(new TcpClientImpl(serverHost, serverPort))
{
}

TcpClient::~TcpClient()
{
}

bool TcpClient::connect()
{
    return this->impl->connect();
}

void TcpClient::sendMessage(const std::string data)
{
    return this->impl->sendMessage(data);
}
