#include <iostream>
#include <map>
#include <string>

#include <wechat_client/wechat_client.h>
#include <spdlog/spdlog.h>
#include <platform_define.h>
#include <util/string_util.h>

int main(int argc, char *argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN

    //ConfigFile file("./configs/system.xml");

    auto list = StringUtil::split("aaaabbaaaabbaabbaaabbccc", "bb");

    for (auto item : list)
    {
        std::cout << item << std::endl;
    }

    return 0;

    WeChatClient client;

    bool flag = client.checkServerOnline();
    if (!flag)
    {
        spdlog::info("server not online...");
    }

    UserInfo user;
    std::string checkErrorInfo;
    user.userName = "admin";
    user.password = "123";

    flag = client.userInfoCheck(user, checkErrorInfo);
    if (flag == true)
    {
        spdlog::info("user info :");
        spdlog::info("{}", client.getCurrentUser()->toJson());
    }

	return 0;
}