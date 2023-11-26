#include "mysql_set.h"
#include <stdexcept>

void MysqlSet::setTableName(std::string tableName)
{
	this->tableName = tableName;
}

std::string MysqlSet::getTableName()
{
	return this->tableName;
}

void MysqlSet::appendFieldName(std::string fieldName)
{
	this->fieldName.emplace_back(std::move(fieldName));
}

void MysqlSet::appendWhereCondition(std::string condition)
{
	this->whereCondition.emplace_back(std::move(condition));
}

const std::vector<std::string>& MysqlSet::getFieldName()
{
	return this->fieldName;
}

std::string MysqlSet::buildFieldNameString()
{
	std::string temp;
	
	for (auto item : this->fieldName)
	{
		temp.push_back('`');
		temp += item;
		temp.push_back('`');
		temp.push_back(',');
	}

	temp.pop_back();

	return std::move(temp);
}

std::string MysqlSet::buildRowDataString(size_t row)
{
	if (row >= this->datas.size()) throw std::out_of_range("row param is out of range");

	std::string temp;

	for (auto item : this->datas[row])
	{
		if (item.isType<std::string>())
		{
			temp.push_back('\"');
			temp += item.toString();
			temp.push_back('\"');
		}
		else
			temp += item.toString();

		temp.push_back(',');
	}

	temp.pop_back();

	return std::move(temp);
}

std::string MysqlSet::buildWhereString()
{
	std::string whereString("where ");
	std::string conditionString;
	for (size_t i = 0; i < this->fieldName.size(); ++i)
	{
		conditionString.push_back('`');
		conditionString += this->fieldName[i];
		conditionString.push_back('`');
		conditionString.push_back('=');

		Data& t = this->datas[0][i];
		if (t.isType<std::string>())
		{
			conditionString.push_back('\"');
			conditionString += t.toString();
			conditionString.push_back('\"');
		}
		else
			conditionString += t.toString();
	}

	if (conditionString.empty())
		return std::string();
	else
		return whereString + conditionString;
}

size_t MysqlSet::rowSize()
{
	return this->datas.size();
}

size_t MysqlSet::colSize()
{
	return this->fieldName.size();
}

const std::vector<Data>& MysqlSet::row(size_t row)
{
	if (row >= this->datas.size()) throw std::out_of_range("row param is out of range");
	return this->datas[row];
}

const Data& MysqlSet::value(size_t row, size_t col)
{
	if (row >= this->datas.size()) throw std::out_of_range("row param is out of range");
	if (col >= this->fieldName.size()) throw std::out_of_range("col param is out of range");

	return this->datas[row][col];
}

std::vector<Data>& MysqlSet::operator[](size_t row)
{
	if (row >= this->datas.size()) throw std::out_of_range("row param is out of range");
	return this->datas[row];
}

void MysqlSet::appendRow(const std::vector<Data>& row)
{
	if (row.size() != this->fieldName.size()) throw std::out_of_range("row param size != field size");

	this->datas.push_back(row);
}
