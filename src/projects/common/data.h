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

    std::string toString();
    int toInt();
    float toFloat();
    double toDouble();
    long toLong();
    bool toBool();

    ~Data() = default;

private:
    std::string data;
};


#endif // !DATA_H