#include <iostream>
#include <map>
#include <string>

#include <tcp_server/server.h>
#include <tcp_server/single_thread_server.h>
#include <spdlog/spdlog.h>
#include <configfile/config_file.h>
#include <spdlog/spdlog.h>
//#include <tcp_server/connection.hpp>
class TcpConnection;

void newCon(TcpConnection* )
{
    spdlog::info("main newCon");
}

void disCon(TcpConnection*)
{
    spdlog::info("main disCon");
}

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

    SingleThreadServer server(serverIp, serverPort);

    server.newConnectionSignal.connect(newCon);
    server.disconnectionSignal.connect(disCon);

    server.run();

	return 0;
}

int main0(int argc, char* argv[])
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