#include "config_file_content_builder_handle_builder.h"
#include "ini_builder_handle.h"
#include "config_file_content_builder_handle.h"

ConfigFileContentBuilderHandle * ConfigFileContentBuilderHandleBuilder::build()
{
    ConfigFileContentBuilderHandle* head = new IniBuilderHandle;
    head->next = nullptr;

    return head;
}