#include "platform_util.h"

#ifdef I_OS_WIN
#include <io.h>
#endif // I_OS_WIN

#ifdef I_OS_LINUX
#include <unistd.h>
#endif // I_OS_LINUX

bool PlatformUtil::access(const char * filename, FileAuthority mode)
{
#ifdef I_OS_WIN
    return ::_access(filename, (int)mode) == 0;
#endif // I_OS_WIN

#ifdef I_OS_LINUX
#include <unistd.h>
    return ::access(filename, (int)mode) == 0;
#endif // I_OS_LINUX
}