#ifndef PLATFORM_UTIL_H
#define PLATFORM_UTIL_H

#include <string>
#include <list>

//平台工具集
class PlatformUtil
{
public:
    enum FileAuthority
    {
        //文件存在
        file_exist = 0,
        //可执行权限 linux
        can_execute = 1,
        //可写入
        can_write = 2,
        //可读取
        can_read = 4,
        //可读写 win
        can_write_read = 6
    };
    
    //检查filename文件的权限authority是否正常, 正常返回true，否则返回false
    static bool access(const char *filename, FileAuthority authority);

    //返回参数对应的文件绝对路径
    static std::string fileAbsolutePath(std::string file);

    //判断参数是否是目录
    static bool isDirectory(std::string file);

    //判断参数是否是文件
    static bool isFile(std::string file);

    //路径标准化
    static std::string standardPath(std::string file);

    //获取目录下所有文件以及子目录
    static std::list<std::string> directoryContent(std::string file);

    //获取计算机上所有光盘驱动器列表
    static std::list<std::string> compactDiscList();
};

#endif // !PLATFORM_UTIL_H