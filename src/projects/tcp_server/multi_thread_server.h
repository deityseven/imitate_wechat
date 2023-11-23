#ifndef MULTI_THREAD_TCP_SERVER_H
#define MULTI_THREAD_TCP_SERVER_H

#include <string>

class MultiThreadServerImpl;

class MultiThreadServer
{
public:
	MultiThreadServer(std::string serverHost, unsigned int serverPort, size_t threadSize);
	~MultiThreadServer();

	void run();

private:
	std::string serverHost;
	size_t serverPort;
	size_t threadSize;
private:
	MultiThreadServerImpl* impl;
};

#endif // !CONFIG_FILE_H