#include <iostream>
#include <map>
#include <string>

#include <tcp_server/server.h>
#include <spdlog/spdlog.h>
#include <configfile/config_file.h>

int main(int argc, char *argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN

    ConfigFile cf("./configs/system.json");
    cf.beginSection("tcp");

    TcpServer server("127.0.0.1", cf.value("serverPort").toInt());
    server.listen();

	return 0;
}