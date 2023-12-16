#include "string_util.h"
#include <algorithm>

std::list<std::string> StringUtil::split(const std::string src, const char sep)
{
    std::list<std::string> content;

    std::string temp;

    for (auto& item : src)
    {
        if (item == sep)
        {
            content.push_back(temp);
            temp.clear();
        }
        else
        {
            temp.push_back(item);
        }
    }

    content.push_back(temp);

    return std::move(content);
}

std::list<std::string> StringUtil::split(const std::string src, const std::string chr)
{
    std::list<std::string> content;

    size_t chrlen = chr.size();

    std::string temp;

    for (size_t currentPos = 0; currentPos < src.size(); )
    {
        size_t pos = src.find(chr, currentPos);

        if (pos != std::string::npos)
        {
            content.emplace_back(src.begin() + currentPos, src.begin() + pos);
            currentPos = pos + chrlen;
        }

        if (pos == std::string::npos)
        {
            content.emplace_back(src.begin() + currentPos, src.end());
            break;
        }
    }

    return std::move(content);
}

std::string StringUtil::eliminate(const std::string src, const char ch)
{
    std::string content;
    content.reserve(src.size());

    for (auto& item : src)
    {
        if (item != ch)
            content.push_back(item);
    }

    return std::move(content);
}

std::string StringUtil::eliminate(const std::string src, const std::string chr)
{
    size_t chrlen = chr.size();

    std::string content;
    content.reserve(src.size());

    for (size_t currentPos = 0; currentPos < src.size(); )
    {
        size_t pos = src.find(chr, currentPos);
        if (pos != std::string::npos)
        {
            content += std::string(src.begin() + currentPos,src.begin() + pos);

            currentPos = pos + chrlen;
        }
    }

    return std::move(content);
}
