#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <asio.hpp>
#include <string>
#include <spdlog/spdlog.h>
#include <signalslot/Signal.hpp>
#include <util/string_util.h>

class TcpConnection
{
signals:
	Gallant::Signal2<TcpConnection*, asio::error_code> disconnectSignal;
	Gallant::Signal1<std::string> receiveMessageSignal;

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

		asio::async_read(this->socketObject,
			asio::buffer(buff),
			std::bind(&TcpConnection::completionCondition, this, std::placeholders::_1, std::placeholders::_2),
			std::bind(&TcpConnection::readSuccess, this, std::placeholders::_1, std::placeholders::_2));
	}

	bool completionCondition(asio::error_code ec, std::size_t size)
	{
		if (ec) return true;

		auto pos = buff.find('|');
		return pos != std::string::npos;
	}

	void readSuccess(asio::error_code ec, std::size_t size)
	{
		if (ec)
		{
			spdlog::info("ec.message : {} ec.value: {} size: {}", ec.message(), ec.value(), size);
			spdlog::info("socket disconnect");
			disconnect(ec);
		}

		if (size != 0)
		{
			this->message += buff;
			spdlog::info("socket recv: {}", this->buff);

			size_t pos = this->message.rfind('|');
			std::string data(this->message.begin(), this->message.begin() + pos);

			spdlog::info("data: {}", data);

			auto list = StringUtil::split(data, '|');
			for (auto& item : list)
			{
				emit receiveMessageSignal(item);
				spdlog::info("emit signal: {}", item);
			}

			if (pos == (this->message.size() - 1)) this->message.clear();
			else
			{
				std::string temp(this->message.begin() + pos + 1, this->message.end());
				this->message = temp;
			}
			
			spdlog::info("message: {}", message);

			emit receiveMessageSignal(data);
		}

		if (this->socketObject.is_open())
		{
			start();
		}
	}

	void disconnect(asio::error_code ec = asio::error_code())
	{
		this->socketObject.shutdown(asio::socket_base::shutdown_type::shutdown_both, ec);
		this->socketObject.close(ec);
		
		emit disconnectSignal(this, ec);
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