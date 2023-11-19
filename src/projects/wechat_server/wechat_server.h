#ifndef SERVER_H
#define SERVER_H

class HttpServer;

class WeChatServer
{
public:
    WeChatServer();
    ~WeChatServer();

private:
    void init();
    HttpServer* httpServer;
};

#endif // !CONFIG_FILE_H