#include "server.h"

#include <asio.hpp>
#include <unordered_map>
#include <spdlog/spdlog.h>

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:

	typedef std::shared_ptr<TcpConnection> pointer;

	TcpConnection(asio::io_context& io_context)
		:socketObject(io_context)
	{

	}

    ~TcpConnection()
    {
        spdlog::info("TcpConnection: ~TcpConnection()");
    }

	asio::ip::tcp::socket& socket() 
	{
		return socketObject;
	}

	void start()
	{
        this->message.clear();
        this->message.resize(1024);

		asio::async_read(this->socketObject, asio::buffer(this->message), std::bind(&TcpConnection::completionCondition, this), std::bind(&TcpConnection::readSuccess, this));
	}

	bool completionCondition()
	{
        spdlog::info("server recv: completionCondition");
		return this->message.find('|') != std::string::npos;
	}

	void readSuccess()
	{
		spdlog::info("server recv: {}", this->message);
	}

private:
	asio::ip::tcp::socket socketObject;
	std::string message;
};

class TcpServerImpl
{
    friend class TcpServer;

public:
	TcpServerImpl(unsigned int serverPort)
		:acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), serverPort))
	{

	}

	TcpConnection::pointer create()
	{
		return TcpConnection::pointer(new TcpConnection(this->io_context));
	}

	void startAccept()
	{
		auto pointer = create();

        spdlog::info("server impl : async_accept");
		this->acceptor.async_accept(pointer->socket(), std::bind(&TcpServerImpl::acceptHandle, this, pointer));

        io_context.run();
	}

	void acceptHandle(TcpConnection::pointer pointer)
	{
		spdlog::info("server impl : acceptHandle");
		pointer->start();

        startAccept();
	}

private:
	asio::io_context io_context;
	asio::ip::tcp::acceptor acceptor;

	std::unordered_map<std::string, TcpConnection::pointer> userList;
};

TcpServer::TcpServer(std::string serverHost, unsigned int serverPort)
	:impl(new TcpServerImpl(serverPort))
{
}

TcpServer::~TcpServer()
{
	delete impl;
}

void TcpServer::listen()
{
	startAccept();
}

void TcpServer::startAccept()
{
	impl->startAccept();
}

