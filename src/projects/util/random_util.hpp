#ifndef RANDOM_UTIL_HPP
#define RANDOM_UTIL_HPP

#include <chrono>
#include <string>
#include <type_traits>

class RandomUtil
{
public:

	static RandomUtil& instance()
	{
		static RandomUtil ins;
		return ins;
	}

	~RandomUtil() = default;

	template<typename T>
	T generateInRange(T min, T max)
	{
		return rand() % ((max + 1) - min) + min;
	}

	template<>
	float generateInRange(float min, float max)
	{
		long minIntegralPart = min;
		long maxIntegralPart = max;

		long integralPartValue = generateInRange(minIntegralPart, maxIntegralPart);

		long fractionalPartValue = generateInRange((long)0, (long)999999);

		char buf[20];
		memset(buf, 0, sizeof(buf));

		sprintf(buf, "%ld.%ld", integralPartValue, fractionalPartValue);

		return std::stof(buf);
	}

	template<>
	double generateInRange(double min, double max)
	{
		long long minIntegralPart = min;
		long long maxIntegralPart = max;

		long long integralPartValue = generateInRange(minIntegralPart, maxIntegralPart);
		long long fractionalPartValue = generateInRange((long long)0, (long long)999999999999999);

		char buf[40];
		memset(buf, 0, sizeof(buf));

		sprintf(buf, "%lld.%lld", integralPartValue, fractionalPartValue);

		return std::stod(buf);
	}

private:
	RandomUtil()
	{
		auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
		long long nsTime = 0;
		memcpy(&nsTime, &now_ns, sizeof(long long));

		std::string nsTimeStr = std::to_string(nsTime);
		std::string firstTenStr;
		firstTenStr.assign(nsTimeStr, 10);
		unsigned int seed = std::stol(firstTenStr);

		srand(seed);
	}
};

#endif // !RANDOM_UTIL_HPP