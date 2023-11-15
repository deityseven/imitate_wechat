#include "config_file.h"
#include "file_util.h"
#include <stdexcept>
#include "./configfile/parser/config_file_content_parser.h"

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
    this->formatData = ConfigFile::Format::none;
    this->filePathData.clear();
}

ConfigFile::Format ConfigFile::format() const
{
    return this->formatData;
}

std::string ConfigFile::filePath() const
{
    return this->filePathData;
}

ConfigFile::ConfigFile(std::string filePath)
    :currentSection("default"),
    formatData(ConfigFile::Format::none), 
    isWritableData(false),
    filePathData(filePath)
{
}

ConfigFile::~ConfigFile()
{
    clear();
}

std::string ConfigFile::readFile(const std::string& filePath) const
{
    return FileUtil::readAllText(filePath);
}

void ConfigFile::parseFile()
{
    bool isWritable = FileUtil::canWrite(this->filePathData);
    setWritable(isWritable);
    auto fileContent = readFile(this->filePathData);
    
    ConfigFileContentParser::instance().parseContent(fileContent, this->data);
}

void ConfigFile::outputFile()
{
    if (this->isWritableData == false) return;

    auto& fileContent = buildFileContent(this->data);
    FileUtil::saveToText(fileContent, this->filePathData);
}

void ConfigFile::setWritable(bool isWritable)
{
    this->isWritableData = isWritable;
}

void ConfigFile::setFormat(Format format)
{
    this->formatData = format;
}
