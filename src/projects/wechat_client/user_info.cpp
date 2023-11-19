#include "user_info.h"
#include <json/json.hpp>

std::string UserInfo::toJson()
{
    nlohmann::json root;

    root["user_name"] = this->userName;
    root["password"] = this->password;
    root["token"] = this->token;
    root["nickname"] = this->nickname;
    root["wechat_id"] = this->wechatID;
    root["region"] = this->region;
    root["signature"] = this->signature;

    return root.dump();
}

UserInfo & UserInfo::fromJson(std::string json)
{
    nlohmann::json root = nlohmann::json::parse(json);

    auto user_name = root["user_name"];
    if (!user_name.is_null()) this->userName = user_name.get<std::string>();
    auto password = root["password"];
    if (!password.is_null()) this->password = password.get<std::string>();
    auto token = root["token"];
    if (!token.is_null()) this->token = token.get<std::string>();
    auto nickname = root["nickname"];
    if (!nickname.is_null()) this->nickname = nickname.get<std::string>();
    auto wechat_id = root["wechat_id"];
    if (!wechat_id.is_null()) this->wechatID = wechat_id.get<std::string>();
    auto region = root["region"];
    if (!region.is_null()) this->region = region.get<std::string>();
    auto signature = root["signature"];
    if (!signature.is_null()) this->signature = signature.get<std::string>();

    return *this;
}
