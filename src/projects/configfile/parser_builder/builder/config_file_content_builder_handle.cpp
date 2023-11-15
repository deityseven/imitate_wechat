#include "config_file_content_parser_handle.h"

bool ConfigFileContentParserHandle::execute(const std::string& configFileContent, const ConfigFileType& type, ConfigData& out)
{
    if (canHandle(type))
        return handle(configFileContent, out);
    else
        return next->execute(configFileContent, type, out);
}
