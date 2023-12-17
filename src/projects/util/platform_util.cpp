#include "platform_util.h"

#ifdef I_OS_WIN
#include <io.h>
#include <stdlib.h>
#endif // I_OS_WIN

#ifdef I_OS_LINUX
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
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
        return std::string(buff);
    }
#endif // I_OS_WIN

#ifdef I_OS_LINUX
    realpath(file.c_str(), buff);
    if (strlen(buff) > 0)
    {
        return std::string(buff);
    }
#endif // I_OS_LINUX

    return std::string();
}
