#include "wechat_server.h"

#include <http_server/server.h>
#include <configfile/config_file.h>
#include <iostream>
#include <spdlog/spdlog.h>

WeChatServer::WeChatServer()
    :httpServer(nullptr)
{
    init();
}

WeChatServer::~WeChatServer()
{
    if (this->httpServer != nullptr) delete this->httpServer;
}

void WeChatServer::init()
{
    ConfigFile cf("./configs/system.json");
    cf.beginSection("http");
    if (this->httpServer == nullptr)
    {
        auto ip = cf.value("serverIp").toString();
        auto port = cf.value("serverPort").toInt();
        spdlog::info("server init, ip:{} port:{}...", ip, port);
        this->httpServer = new HttpServer(ip, port);
        this->httpServer->run();
    }
}
