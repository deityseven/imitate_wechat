#ifndef INI_BUILDER_HANDLE_H
#define INI_BUILDER_HANDLE_H

#include "config_file_content_builder_handle.h"

class IniBuilderHandle : public ConfigFileContentBuilderHandle
{
public:
    IniBuilderHandle();

protected:
    // 通过 ConfigFileContentBuilderHandle 继承
    virtual bool canHandle(const ConfigFileType & type) override;

    virtual bool handle(const std::map<std::string, std::map<std::string, Data>>& data, std::string & out) override;

};

#endif // !CONFIG_FILE_H