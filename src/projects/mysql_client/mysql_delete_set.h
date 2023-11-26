#ifndef MYSQL_DELETE_SET_H
#define MYSQL_DELETE_SET_H

#include "mysql_set.h"

class MysqlDeleteSet : public MysqlSet
{
public:
	MysqlDeleteSet();
	MysqlDeleteSet(std::vector<std::string> fieldName, std::vector<Data> data, std::vector <std::string> whereCondition);
	~MysqlDeleteSet();

};

#endif // !CONFIG_FILE_H