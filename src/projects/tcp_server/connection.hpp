#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <asio.hpp>
#include <string>
#include <spdlog/spdlog.h>

class TcpConnection
{
public:
	TcpConnection(asio::io_context& io_context)
		:socketObject(io_context), bufferSize(4096)
	{
		buff.reserve(bufferSize);
	}

	~TcpConnection()
	{
	}

	asio::ip::tcp::socket& socket()
	{
		return socketObject;
	}

	void sendMessage(const std::string data)
	{
		this->sendMessageData = data;
		asio::async_write(this->socketObject, asio::buffer(this->sendMessageData), std::bind(&TcpConnection::sendSuccess, this, std::placeholders::_1, std::placeholders::_2));
	}

	void sendSuccess(asio::error_code ec, std::size_t size)
	{
		if (ec == asio::error::eof)
		{
			spdlog::info("socket disconnect");
			socketObject.shutdown(asio::socket_base::shutdown_type::shutdown_both);
			socketObject.close();
		}

		if (size == 0)
		{
			spdlog::info("connection sendMessage->sendSuccess->send error...");
		}
	}

	std::string recvWecharId()
	{
		wechatId.resize(10);
		this->socketObject.receive(asio::buffer(wechatId));
		return wechatId;
	}

	void start()
	{
		buff.clear();
		buff.resize(this->bufferSize);
		asio::async_read(this->socketObject, asio::buffer(buff), std::bind(&TcpConnection::completionCondition, this), std::bind(&TcpConnection::readSuccess, this, std::placeholders::_1, std::placeholders::_2));
	}

	bool completionCondition()
	{
		auto pos = buff.find('|');
		return pos != std::string::npos;
	}

	void readSuccess(asio::error_code ec, std::size_t size)
	{
		//spdlog::info("ec.message : {} ec.value: {} size: {}", ec.message(), ec.value(), size);

		if (ec == asio::error::eof)
		{
			spdlog::info("socket disconnect");
			socketObject.shutdown(asio::socket_base::shutdown_type::shutdown_both);
			socketObject.close();
		}

		if (size != 0)
		{
			this->message += buff;
			spdlog::info("socket recv: {}", this->message);
		}

		start();
	}

private:
	asio::ip::tcp::socket socketObject;
	const size_t bufferSize;
	std::string buff;
	std::string message;
	std::string sendMessageData;
	std::string wechatId;
};


#endif // !TCPCONNECTION_H