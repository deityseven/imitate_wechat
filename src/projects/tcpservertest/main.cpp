#include <iostream>
#include <map>
#include <string>

#include <tcp_server/server.h>
#include <spdlog/spdlog.h>
#include <configfile/config_file.h>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN

    ConfigFile cf("./configs/system.json");
    cf.beginSection("tcp");

    std::string serverIp = cf.value("serverIp").toString();
    int serverPort = cf.value("serverPort").toInt();

    spdlog::info("serverIp: {} serverPort: {}", serverIp, serverPort);

    TcpServer server(serverIp, serverPort);
    server.listen();

	return 0;
}