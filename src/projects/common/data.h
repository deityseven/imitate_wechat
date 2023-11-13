#ifndef DATA_H
#define DATA_H

#include <string>

class Data
{
public:
    Data() = default;
    Data(std::string data);
    Data(int data);
    Data(float data);
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

private:
    std::string data;
};


#endif // !DATA_H