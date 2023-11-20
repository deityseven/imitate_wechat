#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>

class TcpClient
{
public:
    TcpClient(std::string serverHost, unsigned int serverPort);
    ~TcpClient();

private:
};

#endif // !CONFIG_FILE_H