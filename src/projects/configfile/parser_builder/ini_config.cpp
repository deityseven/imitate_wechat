#include "ini_config.h"
/*
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

void IniConfig::parseContent(const std::string & fileContent, ConfigData& data)
{
    setFormat(ConfigFile::Format::ini);

    //在文件内容末尾添加新行方便解析
    //add a newline at the end of the file
    std::string fileData = fileContent + '\n';

    StringList list = StringUtil::split(fileData, '\n');

    std::string sectionName = "default";

    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
        auto& line = (*iter);
        //空行处理
        if (line.empty()) continue;

        //不需要解析注释行
        //needn't parse annotation line
        if (line.find('#') != std::string::npos) continue;

        //这一行是key和value，解析他们保存到当前sectionname段下
        //this line is key and value, parse they save to current sectionName.
        if (line.find('=') != std::string::npos)
        {
            StringList keyAndValue = StringUtil::split(line, '=');
            if (keyAndValue.empty()) continue;

            auto iter = keyAndValue.begin();

            std::string key = *iter;
            Data value(*(++iter));

            data[sectionName][key] = value;
        }

        //这行是sectionname
        //this line is section name
        if (line.find('[') != std::string::npos && line.find(']') != std::string::npos)
        {
            //移除[]，并给当前段赋值为sectionName
            //drop []
            sectionName = std::string(line.begin() + 1, line.end() - 1);
        }
    }
}

std::string IniConfig::buildFileContent(const ConfigData& data) const
{
    std::string fileContent;

    //default section
    std::string defaultSectionName = "default";
    auto defaultSectionPair = data.find(defaultSectionName);
    for (auto pair : defaultSectionPair->second)
    {
        const std::string& key = pair.first;
        const Data& value = pair.second;

        fileContent += key;
        fileContent.push_back('=');
        fileContent += value.toString();
        fileContent.push_back('\n');
    }

    //other section
    for (auto& sectionPair : data)
    {
        const std::string& sectionName = sectionPair.first;
        if (sectionPair.first == defaultSectionName) continue;

        //add section name
        fileContent.push_back('\n');
        fileContent.push_back('[');
        fileContent += sectionName;
        fileContent.push_back(']');
        fileContent.push_back('\n');

        //add section's key and value
        for (auto& keyAndValuePair : sectionPair.second)
        {
            const std::string& key = keyAndValuePair.first;
            const Data& value = keyAndValuePair.second;

            fileContent += key;
            fileContent.push_back('=');
            fileContent += value.toString();
            fileContent.push_back('\n');
        }
    }

    return std::move(fileContent);
}
*/
