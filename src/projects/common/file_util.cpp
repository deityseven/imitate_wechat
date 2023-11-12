#include "file_util.h"

#include <fstream>

std::string FileUtil::readAllText(const std::string & filePath)
{
    std::string content;

    std::ifstream fs(filePath);

    if (fs.is_open()) {
        content = std::string((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
        fs.close();
    }

    return std::move(content);
}

bool FileUtil::canWrite(const std::string & filePath)
{
    /*
    std::ofstream fs(filePath);

    if (fs.is_open()) {
        fs.close();
        return true;
    }
    
    if (PlatformUtil::fileAccess(filePath.c_str(), PlatformUtil::FileAuthority::file_exist) == 0)
    {
        if (PlatformUtil::fileAccess(filePath.c_str(), PlatformUtil::FileAuthority::can_write) == 0)
            return true;
    }
    */
    return false;
}

void FileUtil::saveToText(const std::string & fileContent, const std::string & filePath)
{
    std::string content;

    std::ofstream fs(filePath);

    if (fs.is_open()) {
        fs << fileContent;
        fs.close();
    }
}
