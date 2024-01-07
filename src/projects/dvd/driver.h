#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <list>

class Driver
{
public:
	Driver();
	~Driver();

	//获取光盘驱动器列表
	std::list<std::string> getDrivers();

	//弹出驱动器
	bool popup(std::string driver);

private:
	//光盘驱动器列表
	std::list<std::string> drivers;
};

#endif // !DRIVER_H
