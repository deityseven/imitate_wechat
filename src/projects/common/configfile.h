#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <string>
#include <list>
#include <map>

#include "type_struct.h"
#include "data.h"

//配置文件抽象
class ConfigFile
{
public:

    //配置文件格式
    enum Format
    {
        none,
        ini,
        json,
        xml
    };

    //定位到某个section，默认default
    void beginSection(std::string section = "default");
    //结束section定位
    void endSection();
    //当前section
    std::string section() const;
    //获取key对应的值
    Data value(std::string key) const;
    //设置值
    void setValue(std::string key, Data data);
    //返回当前section下所有 key
    StringList allKeys() const;
    //查询当前section下是否存在key，存在返回true
    bool hasKey(std::string key) const;
    //在当前section下删除key以及对应的值，如果key存在并且删除成功返回true
    bool deleteKey(std::string key);
    //同hasKey
    bool contains(std::string key) const;
    //返回当前配置文件是否可以写入
    bool isWritable() const;
    //清空配置内容
    void clear();
    //返回当前配置文件格式
    Format format() const;
    //返回当前配置文件路径
    std::string filePath() const;

    ConfigFile(std::string filePath);
    virtual ~ConfigFile();

protected:
    //解析文件过程
    void parseFile();
    //输出文件过程
    void outputFile();
    //设置文件格式
    void setFormat(Format format);
    //解析文件内容至data中
    virtual void parseContent(const std::string& fileContent, ConfigData& data) = 0;
    //从data中构建配置文件内容
    virtual std::string buildFileContent(const ConfigData& data) const = 0;
private:
    //设置文件是否可写
    void setWritable(bool isWritable);
    //读取文件
    std::string readFile(const std::string& filePath) const;
private:
    //       section               key          value
    ConfigData data;
    //配置文件路径
    std::string filePathData;
    //文件格式
    Format formatData;
    //是否可写入
    bool isWritableData;
    //当前section
    std::string currentSection;
};


#endif // !CONFIG_FILE_H