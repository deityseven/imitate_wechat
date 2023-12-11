#include "account_unique_check.h"
#include <mysql_client/client.h>
#include <configfile/config_file.h>
#include <data.h>
#include <json/json.hpp>

void AccountUniqueCheck::operator()(const httplib::Request& request, httplib::Response& response)
{
	ConfigFile cf("./configs/system.json");
	cf.beginSection("mysql");

	MysqlClient client;

	client.connect(cf.value("serverIp").toString(),
		cf.value("serverPort").toInt(),
		cf.value("databaseName").toString(),
		cf.value("user").toString(),
		cf.value("password").toString());

	std::string userName;
	auto iter = request.params.find("data");
	if (iter != request.params.end())
	{
		std::string data = iter->second;

		auto root = nlohmann::json::parse(data);
		//有bug
		userName = root["user_name"].get<std::string>();
	}

	//"select wechat_id from account where user_name = userName;";
	MysqlQuerySet set;
	set.setTableName("account");
	set.appendQueryFieldName("wechat_id");
	set.appendWhereCondition("=");
	set.appendFieldName("user_name");
	std::vector<Data> row;
	row.push_back(userName);
	set.appendRow(row);
	auto resultSet = client.query(set);

	bool flag = (resultSet.rowSize() <= 0);

	nlohmann::json result;

	result["code"] = 200;
	result["statu"] = flag;
	result["message"] = "success";

	response.body = result.dump();
}
