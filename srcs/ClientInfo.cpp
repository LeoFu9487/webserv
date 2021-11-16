#include "../includes/webserv.hpp"

ClientInfo::ClientInfo(ServerInfo const &server):_server(server), _request("")
{
	
}

void	ClientInfo::set_request(std::string const &str)
{
	_request = str;
}

std::string const &ClientInfo::get_request() const
{
	return _request;
}

ServerInfo const &ClientInfo::get_server() const
{
	return _server;
}