#include "single_thread_server.h"
#include "server_abstract.h"

class SingleThreadServerImpl : public TcpServerAbstract
{
	friend class SingleThreadServer;

public:
	SingleThreadServerImpl(unsigned int serverPort)
		:TcpServerAbstract(serverPort)
	{

	}

	virtual TcpConnection* getConnection() override
	{
		return new TcpConnection(this->io_context);
	}
};

SingleThreadServer::SingleThreadServer(std::string serverHost, unsigned int serverPort)
	:impl(new SingleThreadServerImpl(serverPort)),
	serverHost(serverHost),
	serverPort(serverPort)
{
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
