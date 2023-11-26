#include "mysql_delete_set.h"

MysqlDeleteSet::MysqlDeleteSet()
{
}

MysqlDeleteSet::MysqlDeleteSet(std::vector<std::string> fieldName, std::vector<Data> data, std::vector<std::string> whereCondition)
{
	this->fieldName.swap(fieldName);
	this->datas.push_back(data);
	this->whereCondition = whereCondition;
}

MysqlDeleteSet::~MysqlDeleteSet()
{
}
