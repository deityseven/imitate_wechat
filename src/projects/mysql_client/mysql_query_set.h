#ifndef MYSQL_QUERY_SET_H
#define MYSQL_QUERY_SET_H

#include "mysql_set.h"

class MysqlQuerySet : public MysqlSet
{
public:
	MysqlQuerySet();
	MysqlQuerySet(std::string tableName, std::vector<std::string> fieldName);

	MysqlQuerySet(std::string tableName, std::vector<std::string> fieldName,
		std::vector<Data> data, std::vector<std::string> whereCondition);

	MysqlQuerySet(std::string tableName, std::vector<std::string> fieldName,
		std::vector<Data> data, std::vector<std::string> whereCondition,
		std::string sortFieldName, SortType st);

	MysqlQuerySet::MysqlQuerySet(std::string tableName, std::vector<std::string> fieldName,
		std::string sortFieldName, SortType sortType);

	~MysqlQuerySet();

};

#endif // !CONFIG_FILE_H