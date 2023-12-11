#include "server.h"

#include <http/httplib.h>
#include "handels/server_online.h"
#include "handels/account_verify.h"
#include "handels/account_unique_check.h"

HttpServer::HttpServer(std::string serverHost, unsigned int serverPort)
    :server(nullptr), serverHost(serverHost), serverPort(serverPort)
{
    this->server = new httplib::Server;

    this->server->Post("/api/serverOnline", SeverOnLine());
    this->server->Post("/api/accountVerify", AccountVerify());
    this->server->Post("/api/accountUniqueCheck", AccountUniqueCheck());
}

HttpServer::~HttpServer()
{
    if (this->server != nullptr) delete this->server;
}

void HttpServer::run()
{
    this->server->listen(serverHost.c_str(), serverPort);
}
