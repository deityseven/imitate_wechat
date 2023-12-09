#ifndef MYSQL_SET_H
#define MYSQL_SET_H

#include <string>
#include <vector>
#include <data.h>

class MysqlSet
{
public:

	enum class SortType
	{
		ASC,    //升序
		DESC    //降序
	};


	//表名
	std::string getTableName();
	void setTableName(std::string tableName);
	//设置排序
	void setSortType(SortType sortType);
	//设置排序字段
	void setSortFieldName(std::string sortFieldName);

	//新增字段名
	void appendFieldName(std::string fieldName);
	//新增条件
	void appendWhereCondition(std::string condition);
	//新增查询字段
	void appendQueryFieldName(std::string queryFieldName);
	//新增更新字段
	void appendUpdateFieldName(std::string updateFieldName);
	//新增更新数据
	void appendUpdateRow(const std::vector<Data>& updateRow);

	std::string buildQueryFieldName();
	std::string buildSortString();
	std::string buildFieldNameString();
	std::string buildRowDataString(size_t row);
	std::string buildWhereString();
	std::string buildSetValueString();

	size_t rowSize();
	size_t colSize();

	//访问行数据
	const std::vector<Data>& row(size_t row);
	//访问行列值
	const Data& value(size_t row, size_t col);
	//重载[]提供行数据访问
	std::vector<Data>& operator[](size_t row);
	//新增行数据
	void appendRow(const std::vector<Data>& row);

protected:
	//表名
	std::string tableName;
	//字段名
	std::vector<std::string> fieldName;
	//按行存储数据
	std::vector<std::vector<Data>> datas;
	//条件
	std::vector<std::string> whereCondition;
	//排序字段名
	std::string sortFieldName;
	//排序枚举
	SortType sortType;
	//查询字段
	std::vector<std::string> queryFieldName;
	//更新字段
	std::vector<std::string> updateFieldName;
	//更新
	std::vector<Data> updateDatas;

};

#endif // !CONFIG_FILE_H