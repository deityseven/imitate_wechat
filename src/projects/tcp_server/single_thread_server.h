#ifndef SINGLE_THREAD_TCP_SERVER_H
#define SINGLE_THREAD_TCP_SERVER_H

#include <string>
#include <signalslot/Signal.hpp>

class SingleThreadServerImpl;
class TcpConnection;

class SingleThreadServer
{
signals:
	Gallant::Signal1<TcpConnection*> newConnectionSignal;
	Gallant::Signal1<TcpConnection*> disconnectionSignal;

public:
	SingleThreadServer(std::string serverHost, unsigned int serverPort);
	~SingleThreadServer();

	void run();

	std::string getCurrentError();
private:
	std::string serverHost;
	size_t serverPort;

private:
	void newConnection(TcpConnection* connection);
	void disconnection(TcpConnection* connection);

private:
	SingleThreadServerImpl* impl;
};

#endif // !CONFIG_FILE_H