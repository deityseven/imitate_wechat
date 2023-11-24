#include "multi_thread_server.h"
#include "server_abstract.h"
#include "threadpool.hpp"

std::unordered_map<std::string, TcpConnection*> TcpServerAbstract::userList;

class MultiThreadServerImpl : public TcpServerAbstract
{
	friend class MultiThreadServer;

public:
	MultiThreadServerImpl(unsigned int serverPort, size_t threadSize)
		:TcpServerAbstract(serverPort), threadSize(threadSize), threadPool(threadSize)
	{

	}

	virtual TcpConnection* getConnection() override
	{
		return threadPool.getNewConnection();
	}

	ThreadPool threadPool;
	size_t threadSize;
};

MultiThreadServer::MultiThreadServer(std::string serverHost, unsigned int serverPort, size_t threadSize)
	:impl(new MultiThreadServerImpl(serverPort, threadSize)), 
	threadSize(threadSize),
	serverHost(serverHost),
	serverPort(serverPort)
{
}

MultiThreadServer::~MultiThreadServer()
{
	delete this->impl;
}

void MultiThreadServer::run()
{
	this->impl->startAccept();
	this->impl->io_context.run();
}
