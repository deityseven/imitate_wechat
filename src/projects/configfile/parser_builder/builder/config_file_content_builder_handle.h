#ifndef CONFIG_FILE_CONTENT_BUILDER_HANDLE_H
#define CONFIG_FILE_CONTENT_BUILDER_HANDLE_H

#include "type_struct.h"
#include <string>

class ConfigFileContentBuilderHandle
{
    friend class ConfigFileContentBuilderHandleBuilder;

public:
    bool execute(std::string& configFileContent, const ConfigFileType& type, const ConfigData& out);

protected:
    virtual bool canHandle(const ConfigFileType& type) = 0;
    virtual bool handle(const ConfigData& data, std::string& out) = 0;

private:
    ConfigFileContentBuilderHandle* next;
};

#endif // !CONFIG_FILE_H