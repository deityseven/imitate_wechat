#include <string>
#include "type_struct.h"

//文件相关操作
class StringUtil
{
public:
    //将src字符串按sep字符分割
    static StringList split(const std::string src, const char sep);
    //将src字符串按字串chr分割
    static StringList split(const std::string src, const std::string chr);
    //将src字符串中的所有ch字符剔除
    static std::string eliminate(const std::string src, const char ch);
    //将src字符串中的所有字串chr剔除
    static std::string eliminate(const std::string src, const std::string chr);
};