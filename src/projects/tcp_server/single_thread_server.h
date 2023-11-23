#ifndef SINGLE_THREAD_TCP_SERVER_H
#define SINGLE_THREAD_TCP_SERVER_H

#include <string>

class SingleThreadServerImpl;

class SingleThreadServer
{
public:
	SingleThreadServer(std::string serverHost, unsigned int serverPort);
	~SingleThreadServer();

	void run();

private:
	std::string serverHost;
	size_t serverPort;

private:
	SingleThreadServerImpl* impl;
};

#endif // !CONFIG_FILE_H