#include "webserv.hpp"

bool Cgi::is_cgi(std::map<std::string, std::string> const & cgi_map, std::string const &file_name)
{
	(void)cgi_map;(void)file_name;
	return false;
}
