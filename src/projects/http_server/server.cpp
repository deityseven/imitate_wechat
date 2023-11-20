#include "server.h"

#include <http/httplib.h>
#include "handels/server_online.h"
#include "handels/account_verify.h"

HttpServer::HttpServer(std::string serverHost, unsigned int serverPort)
    :server(nullptr), serverHost(serverHost), serverPort(serverPort)
{
    this->server = new httplib::Server;

    ServerHandle* sh = new SeverOnLine;

    this->server->Post("/api/serverOnline", std::function<void(const httplib::Request& request, httplib::Response& response)>((*sh)));

    this->server->Post("/api/accountVerify", [](const httplib::Request& request, httplib::Response& response) {
         
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
