#include <iostream>
#include <map>
#include <string>

#include <configfile/config_file.h>
#include <tcp_client/client.h>
#include <spdlog/spdlog.h>
#include <platform_define.h>
#include <thread>
#include <signalslot/Signal.hpp>

void recv(std::string data)
{
    spdlog::info("recv: {}", data);
}

int main(int argc, char *argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN

    ConfigFile cf("./configs/system.json");
    cf.beginSection("tcp");

    TcpClient client(cf.value("serverIp").toString(), cf.value("serverPort").toInt());
    
    client.recvMessageSignal.connect(recv);

    if (!client.connect()) return -1;

    client.sendMessage("1234567890");
    client.sendMessage("hello|");
    client.sendMessage("world|cc|");
    client.sendMessage("meto|");

    client.run();

    system("pause");

    return 0;
}

int main0(int argc, char* argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN

    ConfigFile cf("./configs/system.json");
    cf.beginSection("tcp");

    TcpClient client(cf.value("serverIp").toString(), cf.value("serverPort").toInt());

    client.recvMessageSignal.connect(recv);

    if (!client.connect()) return -1;

    client.sendMessage("1234567890");

    client.run();

    system("puse");

    return 0;
}