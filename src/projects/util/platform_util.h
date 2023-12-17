#ifndef PLATFORM_UTIL_H
#define PLATFORM_UTIL_H

#include <string>
#include <platform_define.h>

//文件相关操作
class PlatformUtil
{
public:
    enum FileAuthority
    {
        //文件存在
        file_exist = 0,
#ifdef I_OS_LINUX
        //可执行权限
        can_execute = 1,
#endif // I_OS_LINUX
        //可写入
        can_write = 2,
        //可读取
        cam_read = 4
#ifdef I_OS_WIN
        //可执行权限
        ,can_write_read = 6
#endif // I_OS_LINUX
    };
    
    //检查filename文件的权限authority是否正常, 正常返回true，否则返回false
    static bool access(const char *filename, FileAuthority authority);

    //返回参数对应的文件绝对路径
    static std::string fileAbsolutePath(std::string file);
};

#endif // !PLATFORM_UTIL_H