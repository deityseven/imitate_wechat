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

bool XmlParserHandle::handle(const std::string & content, std::map<std::string, std::map<std::string, Data>>& data)
{
    pugi::xml_document doc;
    auto result = doc.load_string(content.c_str());

    auto root = doc.child("config");
    for (auto section : root)
    {
        std::string sectionName(section.name());
        if (section.first_child().type() != pugi::xml_node_type::node_element)
        {
            sectionName = "default";

            std::string key(section.name());
            std::string value(section.child_value());
            if (value.empty())
            {
                value = section.attribute("value").value();
            }

            data[sectionName][key] = value;
        }

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