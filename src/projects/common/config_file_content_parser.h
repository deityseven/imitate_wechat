#ifndef CONFIG_FILE_CONTENT_PARSER_H
#define CONFIG_FILE_CONTENT_PARSER_H

#include "type_struct.h"
#include <string>

class ConfigFileContentParser
{
public:
	virtual ConfigData parse(std::string fileContent) = 0;
};

#endif // !CONFIG_FILE_H