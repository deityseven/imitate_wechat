#include "wechat_client.h"

#include <http_client/client.h>
#include <common/data.h>
#include <configfile/config_file.h>

WeChatClient::WeChatClient()
    :httpClient(nullptr),
    currentUser(nullptr)
{
    init();
}

WeChatClient::~WeChatClient()
{
    if (this->httpClient != nullptr) delete this->httpClient;
}

bool WeChatClient::checkServerOnline()
{
    return this->httpClient->serverOnline();
}

bool WeChatClient::userInfoCheck(UserInfo user, std::string& checkErrorInfo)
{
    auto findResult =  findUserHistory(user);
    if (findResult == nullptr)
    {
        findResult = new UserInfo;
        this->userHistoryList.push_back(findResult);
    }

    std::string response;
    if (this->httpClient->accountVerify(user.toJson(), response))
    {
        //账户验证通过
        findResult->fromJson(response);
        this->currentUser = findResult;
        return true;
    }
    else
    {
        //账户验证失败
        checkErrorInfo = response;
        this->currentUser = findResult;
        return false;
    }
}

void WeChatClient::init()
{
    ConfigFile cf("./configs/system.json");
    cf.beginSection("http");
    this->serverHost = cf.value("serverIp").toString();
    this->serverPort = cf.value("serverPort").toInt();

    this->httpClient = new HttpClient(this->serverHost,this->serverPort);
    this->httpClient->setReadTimeout(cf.value("readTimeout").toInt());
    this->httpClient->setWriteTimeout(cf.value("writeTimeout").toInt());
}

UserInfo * WeChatClient::findUserHistory(UserInfo & user)
{
    if (user.wechatID.empty()) return nullptr;

    for (auto item : this->userHistoryList)
    {
        if (item->wechatID == user.wechatID) return item;
    }

    return nullptr;
}

UserInfo * WeChatClient::getCurrentUser()
{
    return this->currentUser;
}