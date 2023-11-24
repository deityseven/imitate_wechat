#include "single_thread_server.h"
#include "server_abstract.h"
#include <signalslot/Signal.hpp>

class SingleThreadServerImpl : public TcpServerAbstract
{
	friend class SingleThreadServer;

signals:
	Gallant::Signal1<TcpConnection*> newConnectionSignal;
	Gallant::Signal1<TcpConnection*> disconnectionSignal;

public:
	SingleThreadServerImpl(unsigned int serverPort)
		:TcpServerAbstract(serverPort)
	{

	}

	virtual TcpConnection* getConnection() override
	{
		TcpConnection* connection = new TcpConnection(this->io_context);

		connection->disconnectSignal.connect(this, &SingleThreadServerImpl::disconnection);

		newConnection(connection);

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
};

SingleThreadServer::SingleThreadServer(std::string serverHost, unsigned int serverPort)
	:impl(new SingleThreadServerImpl(serverPort)),
	serverHost(serverHost),
	serverPort(serverPort)
{
	this->impl->newConnectionSignal.connect(this, &SingleThreadServer::newConnection);
	this->impl->disconnectionSignal.connect(this, &SingleThreadServer::disconnection);
}

SingleThreadServer::~SingleThreadServer()
{
	delete this->impl;
}

void SingleThreadServer::run()
{
	this->impl->startAccept();
	this->impl->io_context.run();
}

std::string SingleThreadServer::getCurrentError()
{
	return this->impl->ec.message();
}

void SingleThreadServer::newConnection(TcpConnection* connection)
{
	spdlog::info("SingleThreadServer newConnection");
	emit newConnectionSignal(connection);
}

void SingleThreadServer::disconnection(TcpConnection* connection)
{
	spdlog::info("SingleThreadServer disconnection");
	emit disconnectionSignal(connection);
}
