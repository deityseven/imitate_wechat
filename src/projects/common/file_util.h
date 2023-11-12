#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <string>

//文件相关操作
class FileUtil
{
public:
	// 读取文本文件所有内容
	// filePath的值为文件路径以及文件名
    // 返回文件的所有内容, 如果读取失败返回空内容
	static std::string readAllText(const std::string& filePath);
    // 检测文件是否可以写入
    // filePath的值为文件路径以及文件名
	static bool canWrite(const std::string& filePath);
    // 将fileContent内容刷新到filePath指向的文件中
    // fileContent的值为文件内容
    // filePath的值为文件路径以及文件名
	static void saveToText(const std::string& fileContent, const std::string& filePath);
};

#endif // !FILE_UTIL_H