#include <vector>
#include <thread>
#include <functional>
#include <asio.hpp>
#include "connection.hpp"

class ThreadPool
{
public:
	explicit ThreadPool(size_t threadSize)
		:threadSize(threadSize), 
		currentIoIndex(0)
	{
	}

	void threadRun()
	{
		asio::io_context* context = new asio::io_context;
		asio::io_context::work* work = new asio::io_context::work(*context);
		this->io_contexts.push_back(context);
		works.push_back(work);

		context->run();

		delete context;
		delete work;
	}

	void start()
	{
		for (int i = 0; i < this->threadSize; ++i)
		{
			this->workers.emplace_back(
				std::bind(&ThreadPool::threadRun, this)
			);

			while (this->io_contexts.size() != (i + 1))
			{
				std::this_thread::sleep_for(std::chrono::microseconds(20));
			}
		}
	}

	void stop()
	{
		for (auto item : this->io_contexts)
		{
			if(!item->stopped())
				item->stop();
		}
	}

	TcpConnection* getNewConnection()
	{
		asio::io_context* currentIo = this->io_contexts[currentIoIndex++];
		TcpConnection* connection = new TcpConnection(*currentIo);

		if (this->currentIoIndex == this->io_contexts.size())
			this->currentIoIndex = 0;

		return connection;
	}

private:
	std::vector<std::thread> workers;
	std::vector<asio::io_context*> io_contexts;
	std::vector<asio::io_context::work*> works;
	size_t threadSize;
	size_t currentIoIndex;
};