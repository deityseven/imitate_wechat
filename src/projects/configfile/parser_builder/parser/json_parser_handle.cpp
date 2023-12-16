#include "json_parser_handle.h"
#include <json/json.hpp>

JsonParserHandle::JsonParserHandle()
{
}

bool JsonParserHandle::canHandle(const ConfigFileType & type)
{
    return type == ConfigFileType::Json;
}

bool JsonParserHandle::handle(const std::string & content, std::map<std::string, std::map<std::string, Data>>& data)
{
    std::string fileContent = content;

    nlohmann::json root = nlohmann::json::parse(fileContent);
    auto itemList = root.items();
    for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
    {
        auto key = iter.key();
        auto value = iter.value();

        if (value.is_null()) continue;

        if (value.is_object())
        {
            auto& section = key;
            auto itemList = value.items();
            for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
            {
                auto key = iter.key();
                auto value = iter.value();
                if (value.is_null()) continue;

                if (value.is_string())
                    data[section][key] = value.get<std::string>();
                else if (value.is_boolean())
                    data[section][key] = value.get<bool>();
                else if (value.is_number_integer())
                    data[section][key] = value.get<long>();
                else if (value.is_number_float())
                    data[section][key] = value.get<double>();
            }
        }
        else
        {
            if(value.is_string())
                data["default"][key] = value.get<std::string>();
            else if (value.is_boolean())
                data["default"][key] = value.get<bool>();
            else if (value.is_number_integer())
                data["default"][key] = value.get<long>();
            else if (value.is_number_float())
                data["default"][key] = value.get<double>();
        }
    }

    return true;
}