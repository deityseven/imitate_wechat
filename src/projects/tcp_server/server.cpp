#include "server.h"

#include <asio.hpp>
#include <unordered_map>
#include <spdlog/spdlog.h>
#include <string>

#include "connection.hpp"

class TcpServerImpl
{
	friend class TcpServer;

public:
	TcpServerImpl(unsigned int serverPort)
		:acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), serverPort))
	{

	}

	void startAccept()
	{
		spdlog::info("server impl : startAccept");

		TcpConnection* connection = new TcpConnection(this->io_context);

		this->acceptor.async_accept(connection->socket(), std::bind(&TcpServerImpl::acceptHandle, this, connection));
	}

	void acceptHandle(TcpConnection* connection)
	{
		std::string id = connection->recvWecharId();
		
		spdlog::info("connection recv : id: {}", id);
		
		connection->sendMessage("test send data.|");

		connection->start();

		startAccept();
	}

private:
	asio::io_context io_context;
	asio::ip::tcp::acceptor acceptor;

	std::unordered_map<std::string, TcpConnection*> userList;
};

TcpServer::TcpServer(std::string serverHost, unsigned int serverPort)
	:impl(new TcpServerImpl(serverPort)), serverHost(serverHost), serverPort(serverPort)
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
	impl->io_context.run();
}

#include "threadpool.hpp"

class TcpServerMultiImpl
{
	friend class TcpServerMulti;

public:
	TcpServerMultiImpl(unsigned int serverPort, size_t threadSize)
		:acceptor(accept_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), serverPort)),
		threadSize(threadSize),
		threadPool(threadSize) 
	{
		threadPool.start();
	}

	void startAccept()
	{
		spdlog::info("server impl : startAccept");

		TcpConnection* connection = threadPool.getNewConnection();

		this->acceptor.async_accept(connection->socket(), std::bind(&TcpServerMultiImpl::acceptHandle, this, connection));
	}

	void acceptHandle(TcpConnection* connection)
	{
		std::string id = connection->recvWecharId();

		spdlog::info("connection recv : id: {}", id);

		connection->sendMessage("test send data.|");

		connection->start();

		startAccept();
	}

private:
	asio::io_context accept_io_context;
	asio::ip::tcp::acceptor acceptor;
	ThreadPool threadPool;
	size_t threadSize;
};

TcpServerMulti::TcpServerMulti(std::string serverHost, unsigned int serverPort)
	:impl(new TcpServerMultiImpl(serverPort, serverPort)), serverHost(serverHost), serverPort(serverPort)
{
}

TcpServerMulti::~TcpServerMulti()
{
	delete impl;
}

void TcpServerMulti::listen()
{
	startAccept();
}

void TcpServerMulti::startAccept()
{
	this->impl->startAccept();
	this->impl->accept_io_context.run();
}
