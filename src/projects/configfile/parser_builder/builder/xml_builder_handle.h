#ifndef XML_BUILDER_HANDLE_H
#define XML_BUILDER_HANDLE_H

#include "config_file_content_builder_handle.h"

class XmlBuilderHandle : public ConfigFileContentBuilderHandle
{
public:
    XmlBuilderHandle();

protected:
    // 通过 ConfigFileContentBuilderHandle 继承
    virtual bool canHandle(const ConfigFileType & type) override;

    virtual bool handle(const ConfigData & data, std::string & out) override;

};

#endif // !CONFIG_FILE_H