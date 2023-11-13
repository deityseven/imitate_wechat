#ifndef PLATFORM_UTIL_H
#define PLATFORM_UTIL_H

#include <string>

//文件相关操作
class PlatformUtil
{
public:
    enum FileAuthority
    {
        //文件存在
        file_exist = 0,
        //可执行权限
        can_execute = 1,
        //可写入
        can_write = 2,
        //可读取
        cam_read = 4
    };
    
    //检查filename文件的权限authority是否正常, 正常返回true，否则返回false
    static bool access(const char *filename, FileAuthority authority);
};

#endif // !PLATFORM_UTIL_H