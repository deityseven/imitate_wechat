#include <iostream>
#include <map>
#include <string>

#include <tcp_server/server.h>
#include <tcp_server/multi_thread_server.h>
#include <spdlog/spdlog.h>
#include <configfile/config_file.h>
#include <spdlog/spdlog.h>
#include <tcp_server/connection.hpp>
#include <json/json.hpp>
#include <unordered_map>
#include <cpp-base64/base64.h>

std::unordered_map<std::string, TcpConnection*> list;

void recvMessage(std::string msg)
{
    spdlog::info("main recv:", msg);
    
    std::string temp = msg;

    std::string decodeString = base64_decode(msg);

    spdlog::info("main decodeString:", decodeString);

    auto root = nlohmann::json::parse(decodeString);

    std::string id = root["receiver"].get<std::string>();

    auto iter = list.find(id);
    if (iter == list.end())
    {
        spdlog::error("user: {} not online", id);
        return;
    }

    TcpConnection* con = list[id];

    con->sendMessage(temp);
}

void newCon(TcpConnection* con)
{
    std::string id = con->getWechatId();

    spdlog::info("main newCon id: {}", id);

    list[id] = con;

    con->receiveMessageSignal.connect(recvMessage);
}

void disCon(TcpConnection* con)
{
    std::string id = con->getWechatId();

    spdlog::info("main disCon id: {}", id);

    TcpConnection* con1 = list[id];

    delete con1;

    list.erase(id);
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

    MultiThreadServer server(serverIp, serverPort, 8);

    server.newConnectionSignal.connect(newCon);
    server.disconnectionSignal.connect(disCon);

    server.run();

	return 0;
}