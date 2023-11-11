#include <string>

//文件相关操作
class FileUtil
{
public:
	// 读取文本文件所有内容
	// filePath的值为文件路径以及文件名
    // 返回文件的所有内容, 如果读取失败返回空内容
	static std::string readAllText(const std::string& filePath);
};