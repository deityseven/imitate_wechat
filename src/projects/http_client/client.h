#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

namespace httplib
{
    class Client;
}

class HttpClient
{
public:
    HttpClient(std::string serverHost, unsigned int serverPort);
    ~HttpClient();

    //服务器在线
    bool serverOnline();
    //获取用户信息
    //参数：userInfo 账户信息json数据
    //参数：response 服务器响应 检查通过response存储该账户所有信息 不通过存储异常信息
    bool accountVerify(const std::string userInfo, std::string& response);

    void setReadTimeout(unsigned int millisecond);
    void setWriteTimeout(unsigned int millisecond);
private:
    bool serverIsOnline;

private:
    httplib::Client* client;
};

#endif // !CONFIG_FILE_H