#ifndef MYSQL_INSERT_SET_H
#define MYSQL_INSERT_SET_H

#include "mysql_set.h"

class MysqlInsertSet : public MysqlSet
{
public:
	MysqlInsertSet();
	MysqlInsertSet(std::vector<std::string> fieldName, std::vector<std::vector<Data>> data);
	~MysqlInsertSet();

};

#endif // !CONFIG_FILE_H