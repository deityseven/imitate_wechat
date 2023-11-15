#ifndef CONFIG_FILE_CONTENT_PARSER_H
#define CONFIG_FILE_CONTENT_PARSER_H

#include "type_struct.h"
#include <string>

class ConfigFileContentParserHandle;

class ConfigFileContentParser
{
public:

    static ConfigFileContentParser& instance()
    {
        static ConfigFileContentParser ins;
        return ins;
    }

    void parseContent(const std::string & fileContent, ConfigData& data);

private:
    ConfigFileContentParser();
    //处理器头
    ConfigFileContentParserHandle* handleHead;
};

#endif // !CONFIG_FILE_H