#ifndef ACCOUNT_VERIFY_HANDLE_H
#define ACCOUNT_VERIFY_HANDLE_H

#include "server_handler.h"

class AccountVerify : public ServerHandle
{
public:
	virtual void operator()(const httplib::Request& request, httplib::Response& response) override;
};

#endif // !CONFIG_FILE_H