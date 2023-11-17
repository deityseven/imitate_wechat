#include "xml_parser_handle.h"
#include <pugixml/pugixml.hpp>
#include <pugixml/pugiconfig.hpp>

#include <iostream>

XmlParserHandle::XmlParserHandle()
{
}

bool XmlParserHandle::canHandle(const ConfigFileType & type)
{
    return type == ConfigFileType::Xml;
}

bool XmlParserHandle::handle(const std::string & content, ConfigData & data)
{
    pugi::xml_document doc;
    auto result = doc.load_string(content.c_str());

    auto root = doc.child("config");
    for (auto section : root)
    {
        std::string sectionName(section.name());
        for (auto keyAndValue : section)
        {
            std::string key(keyAndValue.name());
            std::string value(keyAndValue.child_value());
            if (value.empty())
            {
                value = keyAndValue.attribute("value").value();
            }

            data[sectionName][key] = value;
        }
        
    }

    return true;
}