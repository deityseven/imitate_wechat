#include "json_builder_handle.h"
#include <json/json.hpp>

JsonBuilderHandle::JsonBuilderHandle()
{
}

bool JsonBuilderHandle::canHandle(const ConfigFileType & type)
{
    return type == ConfigFileType::Json;
}

bool JsonBuilderHandle::handle(const std::map<std::string, std::map<std::string, Data>>& data, std::string & out)
{
    nlohmann::json root;

    //default section
    std::string defaultSectionName = "default";
    auto defaultSectionPair = data.find(defaultSectionName);
    for (auto pair : defaultSectionPair->second)
    {
        const std::string& key = pair.first;
        const Data& value = pair.second;

        nlohmann::json keyJson;

        if(value.isType<std::string>())
            root[key] = value.toString();
        else if (value.isType<long>())
            root[key] = value.toLong();
        else if (value.isType<double>())
            root[key] = value.toDouble();
        else if (value.isType<bool>())
            root[key] = value.toBool();
    }

    //other section
    for (auto& sectionPair : data)
    {
        const std::string& sectionName = sectionPair.first;
        if (sectionPair.first == defaultSectionName) continue;

        nlohmann::json sectionJson;

        //add section's key and value
        for (auto& keyAndValuePair : sectionPair.second)
        {
            const std::string& key = keyAndValuePair.first;
            const Data& value = keyAndValuePair.second;

            nlohmann::json keyJson;

            if (value.isType<std::string>())
                sectionJson[key] = value.toString();
            else if (value.isType<long>())
                sectionJson[key] = value.toLong();
            else if (value.isType<double>())
                sectionJson[key] = value.toDouble();
            else if (value.isType<bool>())
                sectionJson[key] = value.toBool();
        }

        root[sectionName] = sectionJson;
    }

    out.swap(root.dump(4));

    return true;
}
