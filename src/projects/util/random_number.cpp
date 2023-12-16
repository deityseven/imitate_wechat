#include "random_number.h"
#include <iostream>
#include <chrono>
#include <random>
#include <string>

RandomNumber::RandomNumber()
{
	auto now_ms = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
	long long cc = 0;
	memcpy(&cc, &now_ms, sizeof(long long));

	std::string v;
	std::string tstr = std::to_string(cc);
	v.assign(tstr, 10);
	unsigned int value = std::stol(v);

	srand(value);
}

int RandomNumber::randomNum(int min, int max)
{
	return rand() % (max - min) + min;
}
