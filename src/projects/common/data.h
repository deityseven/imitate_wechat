#ifndef DATA_H
#define DATA_H

#include <string>
#include <typeindex>

class Data
{
public:
    Data(void);
    Data(std::string data);
    Data(double data);
    Data(long data);
    Data(bool data);

    std::string toString() const;
    int toInt() const;
    float toFloat() const;
    double toDouble() const;
    long toLong() const;
    bool toBool() const;

    ~Data() = default;

    template<typename U> 
    bool isType() const
    {
        return typeInfo == std::type_index(typeid(U));
    }

private:
    std::string data;
    std::type_index typeInfo;
};

#endif // !DATA_H