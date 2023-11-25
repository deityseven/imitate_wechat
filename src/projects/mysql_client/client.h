#ifndef MYSQL_CLIENT_H
#define MYSQL_CLIENT_H

#include <string>
#include "mysql_result_set.h"

class MYSQL;

class MysqlClient
{
public:
    MysqlClient();
    ~MysqlClient();

    bool connect(std::string serverHost, unsigned int serverPort, std::string db, std::string user, std::string passwd);
    void disconnect();

    MysqlResultSet query(std::string sqlstr);

private:
    std::string serverHost;
    std::string user;
    std::string passwd;
    std::string db;
    unsigned int serverPort;
    MYSQL* mysql;
};

#endif // !CONFIG_FILE_H