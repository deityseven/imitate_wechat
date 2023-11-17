#include "data.h"

Data::Data(void)
    :typeInfo(typeid(void))
{
}

Data::Data(std::string data)
    : typeInfo(typeid(std::string))
{
    this->data.swap(data);
}

Data::Data(double data)
    : typeInfo(typeid(double))
{
    this->data.swap(std::to_string(data));
}

Data::Data(long data)
    : typeInfo(typeid(long))
{
    this->data.swap(std::to_string(data));
}

Data::Data(bool data)
    : typeInfo(typeid(bool))
{
    if (data == true)
        this->data.swap(std::string("true"));
    else
        this->data.swap(std::string("false"));
}

std::string Data::toString() const
{
    return this->data;
}

int Data::toInt() const
{
    return std::move(std::stoi(this->data.c_str()));
}

float Data::toFloat() const
{
    return std::move(std::stof(this->data.c_str()));
}

double Data::toDouble() const
{
    return std::move(std::stod(this->data));
}

long Data::toLong() const
{
    return std::move(std::stol(this->data.c_str()));
}

bool Data::toBool() const
{
    return this->data == "true";
}
