#include "mysql_query_set.h"

MysqlQuerySet::MysqlQuerySet()
{
}

MysqlQuerySet::MysqlQuerySet(std::string tableName, std::vector<std::string> fieldName)
{
	this->tableName.swap(tableName);
	this->fieldName.swap(fieldName);
}

MysqlQuerySet::MysqlQuerySet(std::string tableName, std::vector<std::string> fieldName, std::vector<Data> data, std::vector<std::string> whereCondition)
{
	this->tableName.swap(tableName);
	this->fieldName.swap(fieldName);
	this->datas.push_back(data);
	this->whereCondition = whereCondition;
}

MysqlQuerySet::MysqlQuerySet(std::string tableName, std::vector<std::string> fieldName, std::vector<Data> data, std::vector<std::string> whereCondition, std::string sortFieldName, SortType sortType)
{
	this->tableName.swap(tableName);
	this->fieldName.swap(fieldName);
	this->datas.push_back(data);
	this->whereCondition = whereCondition;
	this->sortFieldName.swap(sortFieldName);
	this->sortType = sortType;
}

MysqlQuerySet::MysqlQuerySet(std::string tableName, std::vector<std::string> fieldName, std::string sortFieldName, SortType sortType)
{
	this->tableName.swap(tableName);
	this->fieldName.swap(fieldName);
	this->sortFieldName.swap(sortFieldName);
	this->sortType = sortType;
}

MysqlQuerySet::~MysqlQuerySet()
{
}
