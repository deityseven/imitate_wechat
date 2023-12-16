#ifndef CONFIG_FILE_CONTENT_BUILDER_H
#define CONFIG_FILE_CONTENT_BUILDER_H

#include "../../config_file.h"
#include <string>

class ConfigFileContentBuilderHandle;

class ConfigFileContentBuilder
{
public:

    static ConfigFileContentBuilder& instance()
    {
        static ConfigFileContentBuilder ins;
        return ins;
    }

    std::string buildFileContent(const std::map<std::string, std::map<std::string, Data>>& data, 
        const ConfigFileType& type);

private:
    ConfigFileContentBuilder();
    //处理器头
    ConfigFileContentBuilderHandle* handleHead;
};

#endif // !CONFIG_FILE_H