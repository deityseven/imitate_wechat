#include "client.h"

#include <asio.hpp>
#include <spdlog/spdlog.h>

class TcpClientImpl
{
    friend class TcpClient;
public:
    TcpClientImpl(std::string serverHost, unsigned int serverPort)
        :socketObject(io_context), worker(io_context), serverHost(serverHost), serverPort(serverPort), bufferSize(4096), buff(new char[bufferSize])
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

        data += "|";
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
        std::string temp(buff);

        return temp.find('|') != std::string::npos;
    }

    void recvMessage()
    {
        memset(this->buff, 0, this->bufferSize);

        asio::async_read(this->socketObject, 
            asio::buffer(this->buff, this->bufferSize),
            std::bind(&TcpClientImpl::recvMessageCompletionCondition, this),
            std::bind(&TcpClientImpl::receivedMessage, this, std::placeholders::_1, std::placeholders::_2));
    }

    void receivedMessage(asio::error_code ec, size_t size)
    {
        spdlog::info("ec.value: {} size: {}", ec.value(), size);

        if (ec)
        {
            spdlog::info("socket disconnect");
            socketObject.shutdown(asio::socket_base::shutdown_type::shutdown_both);
            socketObject.close();
        }

        if (size != 0)
        {
            std::string temp(this->buff);
            this->data += temp;

            auto pos = this->data.find('|');

            std::string msg(this->data.begin(), this->data.begin() + pos);

            emit recvMessageSignal(msg);

            if (pos == (this->data.size() - 1)) this->data.clear();
            else
            {
                std::string temp(this->data.begin() + pos + 1, this->data.end());
                this->data = temp;
            }
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
    char* buff;
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
    //this->impl->io_context.run();
    this->impl->io_context.run_one();
}

void TcpClient::recvMessage(std::string data)
{
    emit recvMessageSignal(data);
}
