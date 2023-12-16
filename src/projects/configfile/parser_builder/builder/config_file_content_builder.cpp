#include "config_file_content_builder.h"
#include "config_file_content_builder_handle.h"
#include "config_file_content_builder_handle_builder.h"

ConfigFileContentBuilder::ConfigFileContentBuilder()
    :handleHead(ConfigFileContentBuilderHandleBuilder::build())
{
}

std::string ConfigFileContentBuilder::buildFileContent(const std::map<std::string, std::map<std::string, Data>>& data, const ConfigFileType& type)
{
    std::string content;
    handleHead->execute(content, type, data);

    return std::move(content);
}