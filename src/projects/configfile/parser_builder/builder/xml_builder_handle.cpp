#include "xml_builder_handle.h"
#include <pugixml/pugixml.hpp>
#include <pugixml/pugiconfig.hpp>
#include <sstream>

XmlBuilderHandle::XmlBuilderHandle()
{
}

bool XmlBuilderHandle::canHandle(const ConfigFileType & type)
{
    return type == ConfigFileType::Xml;
}

bool XmlBuilderHandle::handle(const std::map<std::string, std::map<std::string, Data>>& data, std::string & out)
{
    pugi::xml_document doc;
    auto root = doc.append_child("config");

    //default section
    std::string defaultSectionName = "default";
    auto defaultSectionPair = data.find(defaultSectionName);
    for (auto pair : defaultSectionPair->second)
    {
        const std::string& key = pair.first;
        const Data& value = pair.second;

        auto node = root.append_child(key.c_str());

        auto attribute = node.append_attribute("value");

        if (value.isType<std::string>())
            attribute.set_value(value.toString().c_str());
        else if (value.isType<long>())
            attribute.set_value(value.toLong());
        else if (value.isType<double>())
            attribute.set_value(value.toDouble());
        else if (value.isType<bool>())
            attribute.set_value(value.toBool());
    }

    //other section
    for (auto& sectionPair : data)
    {
        const std::string& sectionName = sectionPair.first;
        if (sectionPair.first == defaultSectionName) continue;

        auto sectionNode = root.append_child(sectionName.c_str());

        //add section's key and value
        for (auto& keyAndValuePair : sectionPair.second)
        {
            const std::string& key = keyAndValuePair.first;
            const Data& value = keyAndValuePair.second;

            auto keyNode = sectionNode.append_child(key.c_str());

            auto attribute = keyNode.append_attribute("value");

            if (value.isType<std::string>())
                attribute.set_value(value.toString().c_str());
            else if (value.isType<long>())
                attribute.set_value(value.toLong());
            else if (value.isType<double>())
                attribute.set_value(value.toDouble());
            else if (value.isType<bool>())
                attribute.set_value(value.toBool());
        }

    }

    std::stringstream os;
    doc.save(os, "\t", pugi::format_indent);
    out.swap(os.str());

    return true;
}
