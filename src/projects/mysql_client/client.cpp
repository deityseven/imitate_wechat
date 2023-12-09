#include "client.h"
#include <mysql.h>
#include <spdlog/spdlog.h>
#include <iostream>

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
		spdlog::error(mysql_error(this->mysql));
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
	mysql_close(this->mysql);

	delete this->mysql;

	this->mysql = nullptr;
}

bool MysqlClient::insert(MysqlInsertSet data)
{
	mysql_set_server_option(this->mysql, MYSQL_OPTION_MULTI_STATEMENTS_ON);

	std::string tableName = data.getTableName();

	std::string fieldNames = data.buildFieldNameString();

	std::string values;

	std::string allSql;
	for (size_t i = 0; i < data.rowSize(); ++i)
	{
		values = data.buildRowDataString(i);
		static char buf[4096];
		memset(buf, 0, 4096);
		sprintf(buf, "insert into %s(%s) values (%s);", tableName.c_str(), fieldNames.c_str(), values.c_str());

		allSql += buf;
	}

	int flag = mysql_query(this->mysql, allSql.c_str());

	mysql_set_server_option(this->mysql, MYSQL_OPTION_MULTI_STATEMENTS_OFF);

	return flag == 0;
}

bool MysqlClient::deleter(MysqlDeleteSet data)
{
	std::string tableName = data.getTableName();

	std::string whereString = data.buildWhereString();

	static char buf[4096];
	memset(buf, 0, 4096);
	sprintf(buf, "delete from %s %s;", tableName.c_str(), whereString.c_str());

	std::string sql(buf);
	int flag = mysql_query(this->mysql, sql.c_str());

	return flag == 0;
}

MysqlResultSet MysqlClient::query(MysqlQuerySet data)
{
	std::string tableName = data.getTableName();
	std::string queryFieldName = data.buildQueryFieldName();
	std::string whereString = data.buildWhereString();
	std::string sortString = data.buildSortString();

	static char buf[4096];
	memset(buf, 0, 4096);
	sprintf(buf, "select %s from %s %s %s;", queryFieldName.c_str(), tableName.c_str(), whereString.c_str(), sortString.c_str());

	std::string querySql(buf);
	int flag = mysql_query(this->mysql, querySql.c_str());

	if (flag != 0)
	{
		return MysqlResultSet();
	}

	MYSQL_RES* mysql_res = mysql_store_result(this->mysql);

	MysqlResultSet result(mysql_res);

	mysql_free_result(mysql_res);

	return std::move(result);
}

bool MysqlClient::updater(MysqlUpdateSet data)
{
	std::string tableName = data.getTableName();
	std::string setStr = data.buildSetValueString();
	std::string whereString = data.buildWhereString();

	static char buf[4096];
	memset(buf, 0, 4096);
	sprintf(buf, "update %s set %s %s;", tableName.c_str(), setStr.c_str(), whereString.c_str());

	std::string updateSql(buf);
	int flag = mysql_query(this->mysql, updateSql.c_str());

	return flag == 0;
}
