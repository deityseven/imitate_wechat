#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "user_info.h"
#include <list>

class HttpClient;

class WeChatClient
{
public:
    WeChatClient();
    ~WeChatClient();

    //检查服务器是否在线
    bool checkServerOnline();
    //概述：用户验证
    //参数：user 用户信息
    //参数：checkErrorInfo 如果check失败内容为错误信息
    bool userInfoCheck(UserInfo user, std::string& checkErrorInfo);
    //概述：返回当前用户信息
    UserInfo* getCurrentUser();
private:
    void init();
    UserInfo* findUserHistory(UserInfo& user);
private:
    bool serverOnline;
    HttpClient* httpClient;
    std::string serverHost;
    unsigned int serverPort;

    std::list<UserInfo*> userHistoryList;
    UserInfo* currentUser;
};

#endif // !CONFIG_FILE_H