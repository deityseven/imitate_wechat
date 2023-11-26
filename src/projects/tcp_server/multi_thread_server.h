#ifndef MULTI_THREAD_TCP_SERVER_H
#define MULTI_THREAD_TCP_SERVER_H

#include <string>
#include <signalslot/Signal.hpp>

class TcpConnection;
class MultiThreadServerImpl;

class MultiThreadServer
{
signals:
	Gallant::Signal1<TcpConnection*> newConnectionSignal;
	Gallant::Signal1<TcpConnection*> disconnectionSignal;

public:
	MultiThreadServer(std::string serverHost, unsigned int serverPort, size_t threadSize);
	~MultiThreadServer();

	void run();

	std::string getCurrentError();

private:
	void newConnection(TcpConnection* connection);
	void disconnection(TcpConnection* connection);

private:
	std::string serverHost;
	size_t serverPort;
	size_t threadSize;

private:
	MultiThreadServerImpl* impl;
};

#endif // !CONFIG_FILE_H