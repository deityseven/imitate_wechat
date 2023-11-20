#ifndef SERVER_HANDLE_H
#define SERVER_HANDLE_H

#include <http/httplib.h>

class ServerHandle
{
public:
	virtual void operator()(const httplib::Request& request, httplib::Response& response) = 0;
};

#endif // !CONFIG_FILE_H