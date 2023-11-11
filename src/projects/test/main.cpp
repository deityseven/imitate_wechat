#include <common/config_parser.h>

#include <iostream>
#include <map>
#include <string>

struct T
{
	std::string key;
	int value;
};

int main(int argc, char *argv[])
{
	ConfigParser cp("./configs/system.ini");

	std::cout << cp.getValue("key2");
	std::cout << cp.getValue("sysytem","ip");

	return 0;
}

