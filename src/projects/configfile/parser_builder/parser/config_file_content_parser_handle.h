#ifndef CONFIG_FILE_CONTENT_PARSER_HANDLE_H
#define CONFIG_FILE_CONTENT_PARSER_HANDLE_H

#include "../../config_file.h"
#include <string>

class ConfigFileContentParserHandle
{
    friend class ConfigFileContentParserHandleBuilder;

public:
    bool execute(const std::string& configFileContent, const ConfigFileType& type, std::map<std::string, std::map<std::string, Data>>& out);

protected:
    virtual bool canHandle(const ConfigFileType& type) = 0;
    virtual bool handle(const std::string& data, std::map<std::string, std::map<std::string, Data>>& out) = 0;

private:
    ConfigFileContentParserHandle* next;
};

#endif // !CONFIG_FILE_H