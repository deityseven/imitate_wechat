#ifndef CONFIG_FILE_CONTENT_PARSER_HANDLE_H
#define CONFIG_FILE_CONTENT_PARSER_HANDLE_H

#include <type_struct.h>
#include <string>

class ConfigFileContentParserHandle
{
    friend class ConfigFileContentParserHandleBuilder;

public:
    bool execute(const std::string& configFileContent, const ConfigFileType& type, ConfigData& out);

protected:
    virtual bool canHandle(const ConfigFileType& type) = 0;
    virtual bool handle(const std::string& data, ConfigData& out) = 0;

private:
    ConfigFileContentParserHandle* next;
};

#endif // !CONFIG_FILE_H