#ifndef CONFIG_FILE_CONTENT_BUILDER_HANDLE_H
#define CONFIG_FILE_CONTENT_BUILDER_HANDLE_H

#include "../../config_file.h"
#include <string>

class ConfigFileContentBuilderHandle
{
    friend class ConfigFileContentBuilderHandleBuilder;

public:
    bool execute(std::string& configFileContent, const ConfigFileType& type, 
        const std::map<std::string, std::map<std::string, Data>>& out);

protected:
    virtual bool canHandle(const ConfigFileType& type) = 0;
    virtual bool handle(const std::map<std::string, std::map<std::string, Data>>& data, std::string& out) = 0;

private:
    ConfigFileContentBuilderHandle* next;
};

#endif // !CONFIG_FILE_H