#include "config_file.h"
#include <file_util.h>
#include <stdexcept>
#include "./parser_builder/parser/config_file_content_parser.h"
#include "./parser_builder/builder/config_file_content_builder.h"

ConfigFile::ConfigFile(std::string filePath)
    :currentSection("default"),
    typeData(ConfigFileType::None),
    isWritableData(false),
    filePathData(filePath)
{
    parseFile();
}

ConfigFile::~ConfigFile()
{
    outputFile();
}

inline void ConfigFile::beginSection(std::string section)
{
    this->currentSection.swap(section);
}

inline void ConfigFile::endSection()
{
    this->currentSection = std::string("default");
}

inline std::string ConfigFile::section() const
{
    return this->currentSection;
}

inline Data ConfigFile::value(std::string key) const
{
    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        return keyValueMap.at(key);
    }
    catch (...)
    {
        return Data();
    }
}

inline void ConfigFile::setValue(std::string key, Data data)
{
    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        keyValueMap[key] = data;
    }
    catch (...)
    {

    }
}

inline StringList ConfigFile::allKeys() const
{
    StringList list;

    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        for (auto& pair : keyValueMap)
        {
            list.push_back(pair.first);
        }
    }
    catch (...)
    {
        return list;
    }
}

inline bool ConfigFile::hasKey(std::string key) const
{
    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        auto iter = keyValueMap.find(key);

        return iter != keyValueMap.end();
    }
    catch (...)
    {
        return false;
    }
}

bool ConfigFile::deleteKey(std::string key)
{
    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        auto iter = keyValueMap.find(key);
        if (iter == keyValueMap.end()) return false;

        keyValueMap.erase(iter);

        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool ConfigFile::contains(std::string key) const
{
    return hasKey(key);
}

bool ConfigFile::isWritable() const
{
    return this->isWritableData;
}

void ConfigFile::clear()
{
    this->data.clear();
    this->typeData = ConfigFileType::None;
    this->filePathData.clear();
}

ConfigFileType ConfigFile::type() const
{
    return this->typeData;
}

std::string ConfigFile::filePath() const
{
    return this->filePathData;
}


void ConfigFile::parseFile()
{
    bool isWritable = FileUtil::canWrite(this->filePathData);
    setWritable(isWritable);
    auto fileContent = FileUtil::readAllText(this->filePathData);
    //type
    this->typeData = FileUtil::fileContentFormat(fileContent);

    ConfigFileContentParser::instance().parseContent(fileContent, this->typeData, this->data);
}

void ConfigFile::outputFile()
{
    if (this->isWritableData == false) return;

    std::string fileContent = ConfigFileContentBuilder::instance().buildFileContent(this->data, this->typeData);

    FileUtil::saveToText(fileContent, this->filePathData);
}

void ConfigFile::setWritable(bool isWritable)
{
    this->isWritableData = isWritable;
}

void ConfigFile::setFormat(ConfigFileType format)
{
    this->typeData = format;
}
