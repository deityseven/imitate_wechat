#ifndef CONFIG_FILE_CONTENT_PARSER_H
#define CONFIG_FILE_CONTENT_PARSER_H

#include "type_struct.h"
#include <string>

class ConfigFileContentParser
{
public:

    ConfigFileContentParser& instance()
    {
        static ConfigFileContentParser ins;
        return ins;
    }

	virtual ConfigData parse(std::string fileContent) = 0;

private:
    ConfigFileContentParser();
};

#endif // !CONFIG_FILE_H