#include "client.h"
#include <mysql.h>
#include <spdlog/spdlog.h>

MysqlClient::MysqlClient()
	:mysql(nullptr)
{
}

MysqlClient::~MysqlClient()
{
	disconnect();
	mysql_library_end();
} 

bool MysqlClient::connect(std::string serverHost, unsigned int serverPort, std::string db, std::string user, std::string passwd)
{
	this->mysql = new MYSQL;

	if (mysql_library_init(0, nullptr, nullptr) != 0)
	{ 
		spdlog::error("mysql_library_init return not 0");
		return false;
	}

	MYSQL* returnPtr = mysql_init(this->mysql);
	if (returnPtr == nullptr)
	{
		spdlog::error("mysql_init return nullptr");
		return false;
	}

	returnPtr = mysql_real_connect(this->mysql,
		serverHost.c_str(),
		user.c_str(),
		passwd.c_str(),
		db.c_str(),
		serverPort,
		nullptr,
		0);

	if (returnPtr == nullptr)
	{
		spdlog::error("mysql_real_connect return nullptr");
		return false;
	}

	this->serverHost = serverHost;
	this->user = user;
	this->passwd = passwd;
	this->db = db;
	this->serverPort = serverPort;

	return true;
}

void MysqlClient::disconnect()
{
	mysql_shutdown(this->mysql, KILL_CONNECTION);

	delete this->mysql;

	this->mysql = nullptr;
}

MysqlResultSet MysqlClient::query(std::string sqlstr)
{
	int flag = mysql_query(this->mysql, sqlstr.c_str());

	if (flag != 0)
	{
		return MysqlResultSet();
	}

	MYSQL_RES* mysql_res = mysql_store_result(this->mysql);

	MysqlResultSet result(mysql_res);

	mysql_free_result(mysql_res);

	return std::move(result);
}
