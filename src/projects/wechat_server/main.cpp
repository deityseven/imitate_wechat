#include "wechat_server.h"
#include <platform_define.h>
#include <iostream>

int main()
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN

    WeChatServer server;
}