#include "config_file_content_builder_handle_builder.h"
#include "config_file_content_builder_handle.h"
#include "ini_builder_handle.h"
#include "json_builder_handle.h"
#include "xml_builder_handle.h"

ConfigFileContentBuilderHandle * ConfigFileContentBuilderHandleBuilder::build()
{
    ConfigFileContentBuilderHandle* head = new IniBuilderHandle;
    ConfigFileContentBuilderHandle* json = new JsonBuilderHandle;
    ConfigFileContentBuilderHandle* xml = new XmlBuilderHandle;
    head->next = json;
    json->next = xml;
    xml->next = nullptr;

    return head;
}