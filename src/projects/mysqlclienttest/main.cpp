#include <iostream>
#include <map>
#include <string>

#include <configfile/config_file.h>
#include <mysql_client/client.h>
#include <spdlog/spdlog.h>
#include <platform_define.h>
#include <thread>
#include <signalslot/Signal.hpp>

int main(int argc, char *argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001"); 
#endif // WIN

    ConfigFile cf("./configs/system.json");
    cf.beginSection("mysql");

    MysqlClient client;
    
    bool flag = client.connect(cf.value("serverIp").toString(), 
        cf.value("serverPort").toInt(), 
        cf.value("databaseName").toString(), 
        cf.value("user").toString(), 
        cf.value("password").toString());

    if (flag)
    {
        spdlog::info("flag: true");
    }
    else
    {
        spdlog::info("flag: false");
    }

    auto set = client.query("select * from config;");

    std::cout << set[1][2].toString() << std::endl;

    system("pause");

    return 0;
}