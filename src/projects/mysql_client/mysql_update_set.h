#ifndef MYSQL_UPDATE_SET_H
#define MYSQL_UPDATE_SET_H

#include "mysql_set.h"

class MysqlUpdateSet : public MysqlSet
{
public:
	MysqlUpdateSet();

	MysqlUpdateSet(std::string tableName, std::vector<std::string> updateFieldName, std::vector<Data> updateDatas);

	MysqlUpdateSet(std::string tableName, std::vector<std::string> updateFieldName, std::vector<Data> updateDatas,
		std::vector<std::string> fieldName,
		std::vector<Data> whereData, std::vector<std::string> whereCondition);

	~MysqlUpdateSet();

};

#endif // !CONFIG_FILE_H