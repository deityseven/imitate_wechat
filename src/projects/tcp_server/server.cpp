#include "server.h"

#include <asio.hpp>
#include <unordered_map>
#include <spdlog/spdlog.h>


asio::error_code codel;
std::size_t size;

class TcpConnection
{
public:
	TcpConnection(asio::io_context& io_context)
		:socketObject(io_context), bufferSize(4096)
	{
		buff.reserve(bufferSize);
		spdlog::info("TcpConnection: TcpConnection()");
	}

    ~TcpConnection()
    {
        spdlog::info("TcpConnection: ~TcpConnection()");
    }

	asio::ip::tcp::socket& socket() 
	{
		return socketObject;
	}

	void start()
	{
		buff.clear();
		buff.resize(this->bufferSize);
		asio::async_read(this->socketObject, asio::buffer(buff), std::bind(&TcpConnection::CompletionCondition, this), std::bind(&TcpConnection::readSuccess, this, std::placeholders::_1, std::placeholders::_2));
	}

	bool CompletionCondition()
	{
		auto pos = buff.find('|');
		return pos != std::string::npos;
	}

	void readSuccess(asio::error_code ec, std::size_t size)
	{
		spdlog::info("ec.message : {} ec.value: {} size: {}", ec.message(), ec.value(), size);

		if (ec == asio::error::eof)
		{
			spdlog::info("TcpConnection : dis connect");
		}

		if (size != 0)
		{
			this->message += buff;
			spdlog::info("TcpConnection: recv: {}", this->message);
		}

		start();
	}

private:
	asio::ip::tcp::socket socketObject;
	const size_t bufferSize;
	std::string buff;
	std::string message;
};

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
		spdlog::info("server impl : acceptHandle connection ");
		connection->start();

        startAccept();
	}

private:
	asio::io_context io_context;
	asio::ip::tcp::acceptor acceptor;

	std::unordered_map<std::string, TcpConnection*> userList;
};

TcpServer::TcpServer(std::string serverHost, unsigned int serverPort)
	:impl(new TcpServerImpl(serverPort))
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
	try
	{
		impl->startAccept();
		impl->io_context.run();
	}
	catch (asio::error_code& e)
	{
		spdlog::info("server error : {}", e.message());
	}
}

