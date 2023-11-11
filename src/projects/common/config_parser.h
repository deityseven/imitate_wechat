#include <string>

#include <map>

class ConfigParser
{
public:

	ConfigParser(std::string filePath);

	std::string getValue(std::string key);
	std::string getValue(std::string section, std::string key);

	~ConfigParser();

private:
	std::map<std::string, std::map<std::string, std::string>> data;
};