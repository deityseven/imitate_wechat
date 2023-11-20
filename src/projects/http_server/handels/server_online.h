#ifndef SERVER_ONLINE_HANDLE_H
#define SERVER_ONLINE_HANDLE_H

#include "server_handler.h"

class SeverOnLine : public ServerHandle
{
public:
	virtual void operator()(const httplib::Request& request, httplib::Response& response) override;
};

#endif // !CONFIG_FILE_H