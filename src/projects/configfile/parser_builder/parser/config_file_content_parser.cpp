#include "config_file_content_parser.h"
#include "config_file_content_parser_handle.h"
#include "config_file_content_parser_handle_builder.h"
#include <file_util.h>

ConfigFileContentParser::ConfigFileContentParser()
    :handleHead(ConfigFileContentParserHandleBuilder::build())
{
}

void ConfigFileContentParser::parseContent(const std::string & fileContent, const ConfigFileType& type, std::map<std::string, std::map<std::string, Data>>& data)
{
    //handle
    handleHead->execute(fileContent, type, data);
}

