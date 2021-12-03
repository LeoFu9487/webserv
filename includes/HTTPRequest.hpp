#pragma once
#include "webserv.hpp"

/*
source : https://www.ibm.com/docs/en/cics-ts/5.2?topic=protocol-http-requests
*/

class UploadFile;

typedef enum
{
	none,
	redirect,
	autoindex,
	existed_file,
	post_autoindex,
	post_existed_file,
	post_no_get
}Location_behavior;

class HTTPRequest
{
private:

	Location_behavior	_behavior;

	std::string	_file_uri;
	std::string _second_file_uri;

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
	std::vector<UploadFile> _upload_files;


	// std::vector<std::string> _query_string;
	// https://stackoverflow.com/questions/39266970/what-is-the-difference-between-uri-parameters-and-query-strings


// HTTP headers


public:
	HTTPRequest(ServerInfo const &, std::string const &); 
	// method, path, 
	void	check_request(ServerInfo const &server);
	
	void	set_file_uri(std::string const &file_uri);
	void	set_second_file_uri(std::string const &);
	void	set_behavior(Location_behavior behavior);
	void	set_upload_files(std::string const &request);
	
	std::string const &get_file_uri() const;
	std::string const &get_second_file_uri() const;
	Location_behavior	get_behavior() const;
	std::string const &get_method() const;
	std::string const &get_HTTP_versoin() const;
	std::string const &get_content_length() const;
	std::string const &get_content_type() const;
	std::string const &get_boundary() const;
	std::string const &get_accept() const;
	std::vector<UploadFile> const &get_upload_files() const;
	std::string const &get_path() const;


	void	print() const;
};