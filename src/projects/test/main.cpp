#include <config_parser/config_parser.h>

#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << ConfigParser::test();

	std::cout << "change..." << std::endl;


	std::cout << "test..." << std::endl;

	return 0;
}

