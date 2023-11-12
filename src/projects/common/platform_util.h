#ifndef PLATFORM_UTIL_H
#define PLATFORM_UTIL_H

#include <string>

//文件相关操作
class PlatformUtil
{
public:
    enum FileAuthority
    {
        file_exist = 0,
        can_execute = 1,
        can_write = 2,
        cam_read = 4
    };

    static int fileAccess(const char *filename, FileAuthority mode);
};

#endif // !PLATFORM_UTIL_H