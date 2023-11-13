#ifndef INI_CONFIG_H
#define INI_CONFIG_H

#include "configfile.h"
#include "type_struct.h"

class IniConfig : public ConfigFile
{
public:
    IniConfig(std::string filePath);
    ~IniConfig();

protected:
    // 通过 ConfigFile 继承
    virtual void parseContent(const std::string & fileContent, ConfigData& data) override;
    virtual std::string buildFileContent(const ConfigData& data) const override;
};

#endif // !INI_CONFIG_H