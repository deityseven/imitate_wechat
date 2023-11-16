#include "ini_builder_handle.h"
#include "file_util.h"
#include "string_util.h"

IniBuilderHandle::IniBuilderHandle()
{
}

bool IniBuilderHandle::canHandle(const ConfigFileType & type)
{
    return type == ConfigFileType::Ini;
}

bool IniBuilderHandle::handle(const ConfigData & data, std::string & out)
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

    out.swap(fileContent);

    return true;
}
