#ifndef USER_INFO_H
#define USER_INFO_H

#include <string>

class UserInfo
{
    friend class WeChatClient;
public:
    UserInfo() {};
    ~UserInfo() {};

    UserInfo(UserInfo& other) = default;
    UserInfo(UserInfo&& other) = default;

    std::string toJson();
    UserInfo& fromJson(std::string json);
public:
    std::string userName; //帐号
    std::string password; //密码
    std::string token;    //令牌
    std::string nickname; //昵称
    std::string wechatID; //微信id
    std::string region;   //地区
    std::string signature;//个性签名
};

#endif // !CONFIG_FILE_H