#include "config_file_content_parser_handle_builder.h"
#include "ini_parser_handle.h"
#include "json_parser_handle.h"

ConfigFileContentParserHandle * ConfigFileContentParserHandleBuilder::build()
{
    ConfigFileContentParserHandle* head = new IniParserHandle;
    ConfigFileContentParserHandle* json = new JsonParserHandle;

    head->next = json;
    json->next = nullptr;

    return head;
}
