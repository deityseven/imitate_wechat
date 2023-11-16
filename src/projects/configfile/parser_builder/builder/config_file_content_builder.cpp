#include "config_file_content_builder.h"
#include "config_file_content_builder_handle.h"
#include "config_file_content_builder_handle_builder.h"

std::string ConfigFileContentBuilder::buildFileContent(const ConfigData& data, const ConfigFileType& type)
{
    std::string content;
    handleHead->execute(content, type, data);

    return std::move(content);
}

ConfigFileContentBuilder::ConfigFileContentBuilder()
    :handleHead(ConfigFileContentBuilderHandleBuilder::build())
{
}
