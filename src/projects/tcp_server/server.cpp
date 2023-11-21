#include "server.h"

#include <unordered_map>
#include <asio.hpp>
#include <spdlog/spdlog.h>

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:

	typedef std::shared_ptr<TcpConnection> pointer;

	TcpConnection(asio::io_context& io_context)
		:socketObject(io_context)
	{

	}

	asio::ip::tcp::socket& socket() 
	{
		return socketObject;
	}

	void start()
	{
		asio::async_read(this->socketObject, asio::buffer(this->message), std::function<bool(TcpConnection&)>(&TcpConnection::completionCondition), std::bind(&TcpConnection::readSuccess, this));
	}

	bool completionCondition()
	{
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

		this->acceptor.async_accept(pointer->socket(), std::bind(&TcpServerImpl::acceptHandle, this, pointer));

		startAccept();
	}

	void acceptHandle(TcpConnection::pointer pointer)
	{
		spdlog::info("server impl : acceptHandle");
		pointer->start();
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

