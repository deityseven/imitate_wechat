#include "server.h"

#include <http/httplib.h>
#include <json/json.hpp>
#include <spdlog/spdlog.h>

HttpServer::HttpServer(std::string serverHost, unsigned int serverPort)
    :server(nullptr), serverHost(serverHost), serverPort(serverPort)
{
    this->server = new httplib::Server;

    this->server->Post("/api/serverOnline", [](const httplib::Request& request, httplib::Response& response) {
    });

    this->server->Post("/api/accountVerify", [](const httplib::Request& request, httplib::Response& response) {
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
    });
}

HttpServer::~HttpServer()
{
    if (this->server != nullptr) delete this->server;
}

void HttpServer::run()
{
    this->server->listen(serverHost.c_str(), serverPort);
}
