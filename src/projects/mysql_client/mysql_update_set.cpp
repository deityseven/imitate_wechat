#include "mysql_update_set.h"

MysqlUpdateSet::MysqlUpdateSet()
{
}

MysqlUpdateSet::MysqlUpdateSet(std::string tableName, std::vector<std::string> updateFieldName, std::vector<Data> updateDatas)
{
	this->tableName.swap(tableName);
	this->updateFieldName.swap(updateFieldName);
	this->updateDatas.swap(updateDatas);
}

MysqlUpdateSet::MysqlUpdateSet(std::string tableName, std::vector<std::string> updateFieldName, std::vector<Data> updateDatas, std::vector<std::string> fieldName, std::vector<Data> whereData, std::vector<std::string> whereCondition)
{
	this->tableName.swap(tableName);
	this->updateFieldName.swap(updateFieldName);
	this->fieldName.swap(fieldName);
	this->datas.push_back(whereData);
	this->updateDatas.swap(updateDatas);
	this->whereCondition.swap(whereCondition);
}

MysqlUpdateSet::~MysqlUpdateSet()
{
}
