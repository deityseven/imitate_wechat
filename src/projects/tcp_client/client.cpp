#include "client.h"

#include <asio.hpp>
#include <spdlog/spdlog.h>

class TcpClientImpl
{
    friend class TcpClient;
public:
    TcpClientImpl(std::string serverHost, unsigned int serverPort)
        :socketObject(io_context), worker(io_context), serverHost(serverHost), serverPort(serverPort), bufferSize(4096)
    {
        spdlog::info("serverHost: {} port: {}", serverHost, serverPort);
    }

    bool connect()
    {
        try
        {
            socketObject.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(this->serverHost), this->serverPort));
            recvMessage();
            return true;
        }
        catch (...)
        {
            spdlog::error("error: connect failure");
            return false;
        }
    }

    bool sendMessage(std::string data)
    {
        spdlog::info("send: {}", data);

        size_t dataSize = data.size();
        size_t sendSize = this->socketObject.send(asio::buffer(data));
        if (sendSize == dataSize) return true;
        else
        {
            spdlog::error("need send data size: {}, reality send data size: {}", dataSize, sendSize);
            return false;
        }
        //asio::async_write(this->socketObject, asio::buffer(data), std::bind(&TcpClientImpl::writeSuccess, this, std::placeholders::_1, std::placeholders::_2));
    }

    bool recvMessageCompletionCondition()
    {
        return buff.find('|') != std::string::npos;
    }

    void recvMessage()
    {
        buff.clear();
        buff.resize(this->bufferSize);

        asio::async_read(this->socketObject, 
            asio::buffer(buff), 
            std::bind(&TcpClientImpl::recvMessageCompletionCondition, this),
            std::bind(&TcpClientImpl::receivedMessage, this, std::placeholders::_1, std::placeholders::_2));
    }

    void receivedMessage(asio::error_code ec, size_t size)
    {
        spdlog::info("ec.value: {} size: {}", ec.value(), size);

        if (ec == asio::error::eof)
        {
            spdlog::info("socket disconnect");
            socketObject.shutdown(asio::socket_base::shutdown_type::shutdown_both);
            socketObject.close();
        }

        if (size != 0)
        {
            this->data += this->buff;

            auto pos = this->data.find('|');
            recvMessageSignal(std::string(this->data.begin() ,this->data.begin() + pos));

            std::string temp = std::string(std::string(this->data.begin() + pos, this->data.end()));
            this->data = temp;

            
        }

        recvMessage();
    }

signals:
    Gallant::Signal1<std::string> recvMessageSignal;

private:
    std::string serverHost;
    unsigned int serverPort;
    asio::io_context io_context;
    asio::io_context::work worker;
    asio::ip::tcp::socket socketObject;

    const size_t bufferSize;
    std::string buff;
    std::string data;
};


TcpClient::TcpClient(std::string serverHost, unsigned int serverPort)
    :impl(new TcpClientImpl(serverHost, serverPort))
{
    this->impl->recvMessageSignal.connect(this, &TcpClient::recvMessage);
}

TcpClient::~TcpClient()
{
}

bool TcpClient::connect()
{
    return this->impl->connect();
}

bool TcpClient::sendMessage(std::string data)
{
    return this->impl->sendMessage(data);
}

void TcpClient::run()
{
    this->impl->io_context.run();
}

void TcpClient::recvMessage(std::string data)
{
    recvMessageSignal(data);
}
