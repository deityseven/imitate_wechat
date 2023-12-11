#ifndef ACCOUNT_UNIQUE_CHECK_H
#define ACCOUNT_UNIQUE_CHECK_H

#include "server_handler.h"

class AccountUniqueCheck : public ServerHandle
{
public:
	virtual void operator()(const httplib::Request& request, httplib::Response& response) override;
};

#endif // !CONFIG_FILE_H