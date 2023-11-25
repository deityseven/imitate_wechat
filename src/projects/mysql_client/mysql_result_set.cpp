#include "mysql_result_set.h"
#include <mysql.h>
#include <stdexcept>

MysqlResultSet::MysqlResultSet()
{
}

MysqlResultSet::MysqlResultSet(MYSQL_RES* mysql_res)
{
	size_t rows = mysql_num_rows(mysql_res);
	size_t cols = mysql_num_fields(mysql_res);

	std::string returnContent;
	for (int i = 0; i < cols; ++i)
	{
		MYSQL_FIELD* field = mysql_fetch_field(mysql_res);
		appendFieldName(field->name);
	}

	for (int row = 0; row < rows; ++row)
	{
		MYSQL_ROW mysqlRow = mysql_fetch_row(mysql_res);

		std::vector<Data> rowData;

		for (int col = 0; col < cols; ++col)
		{
			rowData.emplace_back(mysqlRow[col]);
		}

		appendRow(rowData);
	}
}

MysqlResultSet::~MysqlResultSet()
{
}
