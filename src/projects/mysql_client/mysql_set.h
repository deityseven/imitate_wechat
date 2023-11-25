#ifndef MYSQL_SET_H
#define MYSQL_SET_H

#include <string>
#include <vector>
#include <data.h>

class MysqlSet
{
public:
	//新增字段名
	void appendFieldName(std::string fieldName);
	//访问数据集
	const std::vector<std::string>& getFieldName();
	//访问行数据
	const std::vector<Data>& row(size_t row);
	//访问行列值
	const Data& value(size_t row, size_t col);
	//重载[]提供行数据访问
	std::vector<Data>& operator[](size_t row);
	//新增行数据
	void appendRow(const std::vector<Data>& row);
protected:
	//字段名
	std::vector<std::string> fieldName;
	//按行存储数据
	std::vector<std::vector<Data>> datas;
};

#endif // !CONFIG_FILE_H