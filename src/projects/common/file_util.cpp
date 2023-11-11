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
