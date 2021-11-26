#pragma once
#include "webserv.hpp"

/*
source : https://www.ibm.com/docs/en/cics-ts/5.2?topic=protocol-http-requests
*/

class Location;

class HTTPRequest
{
private:

	Location const	*_location;
	void	set_location(Location const &location);


//	Request line
	std::string	_method;
	std::string	_path;
	std::string	_HTTP_version;
	// std::vector<std::string> _query_string;
	// https://stackoverflow.com/questions/39266970/what-is-the-difference-between-url-parameters-and-query-strings


// HTTP headers


public:
	HTTPRequest(std::string const &); 
	// method, path, 
	void	check_request(ServerInfo const &server);
	
	Location const	*get_location() const;
};