#include "data.h"
#include <climits>
#include <ctype.h>

Data::Data(void)
    :typeInfo(std::type_index(typeid(void))),
    doubleData(DBL_MAX),
    longData(LONG_MAX),
    boolData(true)
{
}

Data::Data(const char* data)
    :Data(std::string(data))
{
}

Data::Data(std::string data)
    : Data()
{
    this->typeInfo = std::type_index(typeid(std::string));
    this->stringData.swap(data);

    if (data == "true" || data == "false")
    {
        this->boolData = (this->stringData == "true");
        this->typeInfo = std::type_index(typeid(bool));
        return;
    }
    else if (this->stringData.find('.') != std::string::npos)
    {
        auto pos = this->stringData.find('.');
        if (this->stringData.find('.', pos + 1) != std::string::npos)
        {
            return;
        }

        try
        {
            this->doubleData = std::stod(this->stringData);
            this->typeInfo = std::type_index(typeid(double));
            return;
        }
        catch (...)
        {

        }
    }
    else
    {
        bool isdigitFlag = true;
        for (auto& ch : this->stringData)
        {
            if (ch < -1 || ch > 255 || isdigit(ch) == 0 || isxdigit(ch) == 0)
            {
                isdigitFlag = false;
                break;
            }
        }

        if (isdigitFlag == true)
        {
            this->longData = std::stol(this->stringData);
            this->typeInfo = std::type_index(typeid(long));
        }
    }
}

Data::Data(double data)
    : Data()
{
    this->typeInfo = std::type_index(typeid(double));
    this->doubleData = data;
    this->stringData.swap(std::to_string(data));
}

Data::Data(int data)
    :Data(long(data))
{
}

Data::Data(long data)
    : Data()
{
    this->typeInfo = std::type_index(typeid(long));
    this->longData = data;
    this->stringData.swap(std::to_string(data));
}

Data::Data(bool data)
    : Data()
{
    this->typeInfo = std::type_index(typeid(bool));
    this->boolData = data;
    if (data == true)
        this->stringData.swap(std::string("true"));
    else
        this->stringData.swap(std::string("false"));
}

std::string Data::toString() const
{
    return this->stringData;
}

int Data::toInt() const
{
    return (int)this->longData;
}

float Data::toFloat() const
{
    return (float)this->doubleData;
}

double Data::toDouble() const
{
    return this->doubleData;
}

long Data::toLong() const
{
    return this->longData;
}

bool Data::toBool() const
{
    return this->boolData;
}
