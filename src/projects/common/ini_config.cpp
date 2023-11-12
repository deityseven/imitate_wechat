#include "ini_config.h"
#include "string_util.h"

IniConfig::IniConfig(std::string filePath)
    :ConfigFile(filePath)
{
    parseFile();
}

IniConfig::~IniConfig()
{
    outputFile();
}

void IniConfig::parseContent(const std::string & fileContent, std::map<std::string, std::map<std::string, Data>>& data)
{
    setFormat(ConfigFile::Format::ini);

    std::string fileData = fileContent + '\n';

    StringList list = StringUtil::split(fileData, '\n');

    std::string sectionName = "default";

    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
        auto& line = (*iter);

        //auto& line = StringUtil::eliminate(data, '\n');

        if (line.find('#') != std::string::npos) continue;

        if (line.find('=') != std::string::npos)
        {
            StringList keyAndValue = StringUtil::split(line, '=');
            if (keyAndValue.empty()) continue;

            auto iter = keyAndValue.begin();

            std::string key = *iter;
            Data value(*(++iter));

            data[sectionName][key] = value;
        }

        if (line.find('[') != std::string::npos && line.find(']') != std::string::npos)
        {
            sectionName = std::string(line.begin() + 1, line.end() - 1);
        }
    }
}

std::string && IniConfig::buildFileContent(const std::map<std::string, std::map<std::string, Data>>& data) const
{
    return std::string();
}
