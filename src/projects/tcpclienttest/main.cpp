#include <iostream>
#include <map>
#include <string>

#include <configfile/config_file.h>
#include <tcp_client/client.h>
#include <spdlog/spdlog.h>
#include <platform_define.h>

int main(int argc, char *argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN

    ConfigFile cf("./configs/system.json");
    cf.beginSection("tcp");

    TcpClient client(cf.value("serverIp").toString(), cf.value("serverPort").toInt());
    client.connect();

    client.sendMessage("1234567890");

    while (1)
    {
    }

    system("puse");

    return 0;
}