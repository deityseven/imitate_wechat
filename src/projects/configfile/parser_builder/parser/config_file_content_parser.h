#ifndef CONFIG_FILE_CONTENT_PARSER_H
#define CONFIG_FILE_CONTENT_PARSER_H

#include "../../config_file.h"
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

    void parseContent(const std::string & fileContent, const ConfigFileType& type, 
        std::map<std::string, std::map<std::string, Data>>& data);

private:
    ConfigFileContentParser();
    //处理器头
    ConfigFileContentParserHandle* handleHead;
};

#endif // !CONFIG_FILE_H