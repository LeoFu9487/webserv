#pragma once
#include "webserv.hpp"

class Cgi
{
private:

public:
	static bool	is_cgi(std::map<std::string, std::string> const & cgi_map, std::string const &file_name);
};
