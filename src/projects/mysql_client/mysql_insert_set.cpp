#include "mysql_insert_set.h"

MysqlInsertSet::MysqlInsertSet()
{
}

MysqlInsertSet::MysqlInsertSet(std::vector<std::string> fieldName, std::vector<std::vector<Data>> data)
{
	this->fieldName.swap(fieldName);
	this->datas.swap(data);
}

MysqlInsertSet::~MysqlInsertSet()
{
}
