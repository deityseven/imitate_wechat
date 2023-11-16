#ifndef CONFIG_FILE_CONTENT_BUILDER_H
#define CONFIG_FILE_CONTENT_BUILDER_H

#include "type_struct.h"
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

    std::string buildFileContent(const ConfigData& data, const ConfigFileType& type);

private:
    ConfigFileContentBuilder();
    //处理器头
    ConfigFileContentBuilderHandle* handleHead;
};

#endif // !CONFIG_FILE_H