#include "mysql_set.h"
#include <stdexcept>

void MysqlSet::appendFieldName(std::string fieldName)
{
	this->fieldName.emplace_back(std::move(fieldName));
}

const std::vector<std::string>& MysqlSet::getFieldName()
{
	return this->fieldName;
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
