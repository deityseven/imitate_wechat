#ifndef MYSQL_CLIENT_H
#define MYSQL_CLIENT_H

#include <string>
#include "mysql_result_set.h"
#include "mysql_insert_set.h"
#include "mysql_delete_set.h"
#include "mysql_query_set.h"
#include "mysql_update_set.h"

class MYSQL;

class MysqlClient
{
public:
    MysqlClient();
    ~MysqlClient();

    bool connect(std::string serverHost, unsigned int serverPort, std::string db, std::string user, std::string passwd);
    void disconnect();

    bool insert(MysqlInsertSet data);
    bool deleter(MysqlDeleteSet data);
    MysqlResultSet query(MysqlQuerySet data);
    bool update(MysqlUpdateSet data);

private:
    std::string serverHost;
    std::string user;
    std::string passwd;
    std::string db;
    unsigned int serverPort;
    MYSQL* mysql;
};

#endif // !CONFIG_FILE_H