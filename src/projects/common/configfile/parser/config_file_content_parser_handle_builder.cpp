#include "config_file_content_parser_handle_builder.h"
#include "ini_parser_handle.h"

ConfigFileContentParserHandle * ConfigFileContentParserHandleBuilder::build()
{
    ConfigFileContentParserHandle* head = new IniParserHandle;
    head->next == nullptr;

    return head;
}
