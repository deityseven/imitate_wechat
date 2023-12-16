#include "config_file_content_builder_handle.h"

bool ConfigFileContentBuilderHandle::execute(std::string & configFileContent, const ConfigFileType & type, const std::map<std::string, std::map<std::string, Data>>& data)
{
    if (canHandle(type))
    {
        return handle(data, configFileContent);
    }
    else
    {
        if (next != nullptr)
            return next->execute(configFileContent, type, data);
    }

    return false;
}
