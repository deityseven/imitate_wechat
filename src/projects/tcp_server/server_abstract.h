#ifndef TCP_SERVER_ABSTRACT_H
#define TCP_SERVER_ABSTRACT_H

#include <string>
#include <memory>
#include <asio.hpp>
#include "connection.hpp"

class TcpServerAbstract
{
public:
	TcpServerAbstract(unsigned int serverPort)
		:acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), serverPort))
	{
	}

	virtual TcpConnection* getConnection() = 0;

	void startAccept()
	{
		spdlog::info("server impl : startAccept");

		TcpConnection* connection = getConnection();

		this->acceptor.async_accept(connection->socket(), std::bind(&TcpServerAbstract::acceptHandle, this, connection));
	}

	void acceptHandle(TcpConnection* connection)
	{
		std::string id = connection->recvWecharId();

		userList[id] = connection;

		connection->start();

		startAccept();
	}

protected:
	asio::io_context io_context;
	asio::ip::tcp::acceptor acceptor;

public:
	static std::unordered_map<std::string, TcpConnection*> userList;
};


#endif // !CONFIG_FILE_H