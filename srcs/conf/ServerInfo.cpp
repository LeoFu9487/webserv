#include "../../includes/ServerInfo.hpp"

int	ServerInfo::get_port() const
{
	return _port;
}

std::string const	&ServerInfo::get_IP() const
{
	return _IP;
}

int	ServerInfo::get_max_client() const
{
	return _max_client;
}

#ifdef TEST
ServerInfo::ServerInfo()
{
	_port = 8080;
	_IP = "0.0.0.0";
	_max_client = 100;
}
#endif
