#include "json_parser_handle.h"
#include <json/json.hpp>

JsonParserHandle::JsonParserHandle()
{
}

bool JsonParserHandle::canHandle(const ConfigFileType & type)
{
    return type == ConfigFileType::Json;
}

bool JsonParserHandle::handle(const std::string & content, ConfigData & data)
{
    std::string fileContent = content;

    printf("%s", fileContent.c_str());

    nlohmann::json root = nlohmann::json::parse(fileContent);
    auto itemList = root.items();
    for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
    {
        auto key = iter.key();
        auto value = iter.value();
        if (value.is_object())
        {
            auto itemList = value.items();
            for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
            {
                auto key = iter.key();
                auto value = iter.value();
            }
        }
        else
        {
            data["default"][key] = Data(value.get<std::string>());
        }
    }
}