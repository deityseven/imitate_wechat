#include "multi_thread_server.h"
#include "server_abstract.h"
#include "threadpool.hpp"
#include "connection.hpp"

class MultiThreadServerImpl : public TcpServerAbstract
{
	friend class MultiThreadServer;

signals:
	Gallant::Signal1<TcpConnection*> newConnectionSignal;
	Gallant::Signal1<TcpConnection*> disconnectionSignal;

public:
	MultiThreadServerImpl(unsigned int serverPort, size_t threadSize)
		:TcpServerAbstract(serverPort), threadSize(threadSize), threadPool(threadSize)
	{

	}

	virtual TcpConnection* getConnection() override
	{
		TcpConnection* connection = threadPool.getNewConnection();

		connection->disconnectSignal.connect(this, &MultiThreadServerImpl::disconnection);
		connection->connectedSignal.connect(this, &MultiThreadServerImpl::newConnection);

		return connection;
	}

private:
	void newConnection(TcpConnection* connection)
	{
		spdlog::info("SingleThreadServerImpl newConnection");
		emit newConnectionSignal(connection);
	}

	void disconnection(TcpConnection* connection, asio::error_code ec)
	{
		spdlog::info("SingleThreadServerImpl disconnection");
		this->ec = ec;
		emit disconnectionSignal(connection);
	}

	asio::error_code ec;

	ThreadPool threadPool;
	size_t threadSize;
};

MultiThreadServer::MultiThreadServer(std::string serverHost, unsigned int serverPort, size_t threadSize)
	:impl(new MultiThreadServerImpl(serverPort, threadSize)), 
	threadSize(threadSize),
	serverHost(serverHost),
	serverPort(serverPort)
{
	this->impl->newConnectionSignal.connect(this, &MultiThreadServer::newConnection);
	this->impl->disconnectionSignal.connect(this, &MultiThreadServer::disconnection);
}

MultiThreadServer::~MultiThreadServer()
{
	delete this->impl;
}

void MultiThreadServer::run()
{
	this->impl->threadPool.start();
	this->impl->startAccept();
	this->impl->io_context.run();
}

std::string MultiThreadServer::getCurrentError()
{
	return this->impl->ec.message();
}

void MultiThreadServer::newConnection(TcpConnection* connection)
{
	spdlog::info("SingleThreadServer newConnection");
	emit newConnectionSignal(connection);
}

void MultiThreadServer::disconnection(TcpConnection* connection)
{
	spdlog::info("SingleThreadServer disconnection");
	emit disconnectionSignal(connection);
}
