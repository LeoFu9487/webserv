#include "../includes/webserv.hpp"

ClientInfo::ClientInfo():_request("")
{

}

void	ClientInfo::set_request(char *str, ssize_t len)
{
	str[len] = 0;
	_request = std::string(str);
}

std::string const &ClientInfo::get_request() const
{
	return _request;
}