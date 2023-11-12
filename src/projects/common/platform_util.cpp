#include "platform_util.h"
#include "platform_define.h"

#ifdef I_OS_WIN
#include <io.h>
#endif // I_OS_WIN

#ifdef I_OS_LINUX
#include <unistd.h>
#endif // I_OS_LINUX

int PlatformUtil::fileAccess(const char * filename, FileAuthority mode)
{
    return access(filename, (int)mode);
}