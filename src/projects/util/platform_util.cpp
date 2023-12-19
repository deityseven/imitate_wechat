#include "platform_util.h"

#include <sys/stat.h>
#include <algorithm>

#ifdef I_OS_WIN
#include <io.h>
#include <stdlib.h>
#endif // I_OS_WIN

#ifdef I_OS_LINUX
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#endif // I_OS_LINUX

bool PlatformUtil::access(const char * filename, FileAuthority mode)
{
#ifdef I_OS_WIN
    return ::_access(filename, (int)mode) == 0;
#endif // I_OS_WIN

#ifdef I_OS_LINUX
    return ::access(filename, (int)mode) == 0;
#endif // I_OS_LINUX
}

std::string PlatformUtil::fileAbsolutePath(std::string file)
{
    static char buff[500];
    static size_t buffLen = sizeof(buff);
    memset(buff, 0, buffLen);

#ifdef I_OS_WIN
    if (_fullpath(buff, file.c_str(), buffLen) != nullptr)
    {
        return standardPath(std::string(buff));
    }
#endif // I_OS_WIN

#ifdef I_OS_LINUX
    realpath(file.c_str(), buff);
    if (strlen(buff) > 0)
    {
        std::string result(buff);
        std::replace(result.begin(), result.end(), '\\', '/');
        return result;
    }
#endif // I_OS_LINUX

    return std::string();
}

bool PlatformUtil::isDirectory(std::string file)
{
    struct stat st;
    if (stat(file.c_str(), &st) == 0)
    {
        return st.st_mode & S_IFDIR;
    }

    throw std::exception("invalid parameter");
}

bool PlatformUtil::isFile(std::string file)
{
    struct stat st;
    if (stat(file.c_str(), &st) == 0)
    {
        return st.st_mode & S_IFREG;
    }

    throw std::exception("invalid parameter");
}

std::string PlatformUtil::standardPath(std::string file)
{
    std::replace(file.begin(), file.end(), '\\', '/');
    if (isDirectory(file))
    {
        auto iter = file.rbegin();
        if ((*iter) != '/')
        {
            file.push_back('/');
        }
    }

    return std::move(file);
}

std::list<std::string> PlatformUtil::directoryContent(std::string file)
{
    std::list<std::string> result;

    std::string absPath = fileAbsolutePath(file);
    if (!absPath.empty()) file = absPath;

    if (isDirectory(file))
    {
#ifdef I_OS_WIN
        std::string search = file + "*";
        struct _finddata_t fileInfo;
        memset(&fileInfo, 0, sizeof(struct _finddata_t));
        auto handle = _findfirst(search.c_str(), &fileInfo);
        if (handle == -1) throw std::exception("invalid parameter");
        do
        {
            if(strcmp(".", fileInfo.name) == 0 || strcmp("..", fileInfo.name) == 0)
                continue;
            result.push_back(standardPath(file + fileInfo.name));
        } while (!_findnext(handle, &fileInfo));

#endif // I_OS_WIN

#ifdef I_OS_LINUX
        DIR* dir = opendir(file.c_str());

        if (dir != nullptr)
        {
            while (dirent* info = readdir(dir))
            {
                if (strcmp(".", info->d_name) == 0 || strcmp("..", info->d_name) == 0)
                    result.push_back(standardPath(file + fileInfo.name));
            }

            closedir(dir);
        }
#endif // I_OS_LINUX
    }
    else
    {
        throw std::exception("invalid parameter");
    }

    return result;
}
