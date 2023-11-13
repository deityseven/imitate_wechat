#include "data.h"

Data::Data(std::string data)
{
    this->data.swap(data);
}

Data::Data(int data)
{
    this->data.swap(std::to_string(data));
}

Data::Data(float data)
{
    this->data.swap(std::to_string(data));
}

Data::Data(double data)
{
    this->data.swap(std::to_string(data));
}

Data::Data(long data)
{
    this->data.swap(std::to_string(data));
}

Data::Data(bool data)
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