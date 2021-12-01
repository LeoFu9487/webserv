#pragma once
#include "webserv.hpp"

/*
source : https://www.ibm.com/docs/en/cics-ts/5.2?topic=protocol-http-requests
*/

typedef enum
{
	none,
	redirect,
	autoindex,
	existed_file
}Location_behavior;

class HTTPRequest
{
private:

	Location_behavior	_behavior;

	std::string	_file_uri;

//	Request line
	std::string	_method;
	std::string	_path;
	std::string	_HTTP_version;
	
	// if _method == "POST"
	std::string _content_length; // if too long throw
	// content type and accept : https://stackoverflow.com/questions/35722586/header-parameters-accept-and-content-type-in-a-rest-context#:~:text=So%3A%20Accept%20indicates%20what%20kind,a%20content%2Dtype%20request%20header.
	std::string _content_type; // if not found throw
	std::string _boundary;
	std::string _accept;
	std::vector<std::string> _content;


	// std::vector<std::string> _query_string;
	// https://stackoverflow.com/questions/39266970/what-is-the-difference-between-uri-parameters-and-query-strings


// HTTP headers


public:
	HTTPRequest(std::string const &); 
	// method, path, 
	void	check_request(ServerInfo const &server);
	
	void	set_file_uri(std::string const &file_uri);
	void	set_behavior(Location_behavior behavior);
	
	
	std::string const &get_file_uri() const;
	Location_behavior	get_behavior() const;
	std::string const &get_method() const;
	std::string const &get_HTTP_versoin() const;
	std::string const &get_content_length() const;
	std::string const &get_content_type() const;
	std::string const &get_boundary() const;
	std::string const &get_accept() const;
	std::vector<std::string> const &get_content() const;

	void	print() const;
};