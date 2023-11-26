#include <iostream>
#include <map>
#include <string>

#include <configfile/config_file.h>
#include <tcp_client/client.h>
#include <spdlog/spdlog.h>
#include <platform_define.h>
#include <thread>
#include <signalslot/Signal.hpp>
#include <json/json.hpp>
#include <cpp-base64/base64.h>

void recv(std::string data)
{
    std::string msg = base64_decode(data);

    spdlog::info("main recv: {}", msg);
}

int main(int argc, char *argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN

    std::string idstr;
    long id;
    if (argc == 1)
    {
        idstr = "1000000002";
        id = std::stol(idstr);
    }
    else
    {
        idstr = argv[1];
        id = std::stol(argv[1]);
    }

    ConfigFile cf("./configs/system.json");
    cf.beginSection("tcp");

    TcpClient client(cf.value("serverIp").toString(), cf.value("serverPort").toInt());
    
    client.recvMessageSignal.connect(recv);

    if (!client.connect()) return -1;

    client.sendMessage(idstr);

    while (1)
    {
        nlohmann::json root;

        root["receiver"] = "1000000002";
        root["sender"] = idstr;
        root["dataType"] = 1;
        root["data"] = "hello world";

        std::string msg = root.dump();

        std::string base64msg = base64_encode(msg);

        client.sendMessage(base64msg);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    system("pause");

    return 0;
}