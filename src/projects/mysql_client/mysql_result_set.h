#ifndef MYSQL_RESULT_SET_H
#define MYSQL_RESULT_SET_H

#include "mysql_set.h"

class MYSQL_RES;

class MysqlResultSet : public MysqlSet
{
public:
	MysqlResultSet();
	explicit MysqlResultSet(MYSQL_RES* mysql_res);
	~MysqlResultSet();
};

#endif // !CONFIG_FILE_H