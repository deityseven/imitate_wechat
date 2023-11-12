#ifndef INI_CONFIG_H
#define INI_CONFIG_H

#include "configfile.h"

class IniConfig : public ConfigFile
{
public:
    IniConfig(std::string filePath);
    ~IniConfig();

    // 通过 ConfigFile 继承
    virtual void parseContent(const std::string & fileContent, std::map<std::string, std::map<std::string, Data>>& data) override;
    virtual std::string && buildFileContent(const std::map<std::string, std::map<std::string, Data>>& data) const override;
};

#endif // !INI_CONFIG_H