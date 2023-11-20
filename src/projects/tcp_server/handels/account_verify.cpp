#include "account_verify.h"
#include <json/json.hpp>
#include <string>
#include <spdlog/spdlog.h>

void AccountVerify::operator()(const httplib::Request& request, httplib::Response& response)
{
    auto userInfo = nlohmann::json::parse(request.body);

    std::string userName = userInfo["user_name"].get<std::string>();
    std::string password = userInfo["password"].get<std::string>();

    spdlog::info("server api : accountVerify");
    spdlog::info("user_name: {} password: {}", userName, password);

    if (userName == "admin")
    {
        userInfo["token"] = "jigofmlxhfdlsjgdhsboleh4sg";
        userInfo["nickname"] = "管理员";
        userInfo["wechat_id"] = "admin001";
        userInfo["region"] = "北京";
        userInfo["signature"] = "默认签名";
    }

    nlohmann::json responseJson;
    responseJson["code"] = 200;
    responseJson["statu"] = true;
    responseJson["data"] = userInfo;

    response.body = responseJson.dump();
}