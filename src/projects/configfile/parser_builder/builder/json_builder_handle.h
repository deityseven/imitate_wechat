#ifndef JSON_BUILDER_HANDLE_H
#define JSON_BUILDER_HANDLE_H

#include "config_file_content_builder_handle.h"

class JsonBuilderHandle : public ConfigFileContentBuilderHandle
{
public:
    JsonBuilderHandle();

protected:
    // 通过 ConfigFileContentBuilderHandle 继承
    virtual bool canHandle(const ConfigFileType & type) override;

    virtual bool handle(const std::map<std::string, std::map<std::string, Data>>& data, std::string & out) override;

};

#endif // !CONFIG_FILE_H