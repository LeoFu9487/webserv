#include "../../includes/webserv.hpp"

std::map<int, std::string> HTTPResponse::_status_line = init_code_status();
std::map<std::string, std::string> HTTPResponse::_content_type = init_content_type();

void HTTPResponse::set_HTTP_version(std::string const &str) { _HTTP_version = str; }
void HTTPResponse::set_status_code(status_code status) { if (_status_code == Undefined) _status_code = status;}
void HTTPResponse::set_file_uri(std::string const &uri) { _file_uri = uri; }

std::string const &HTTPResponse::get_HTTP_version() const { return _HTTP_version; }
status_code HTTPResponse::get_status_code() const { return _status_code; }
std::string const &HTTPResponse::get_file_uri() const { return _file_uri; }
std::string const &HTTPResponse::get_msg() const { return _msg; }

std::map<int, std::string> HTTPResponse::init_code_status()
{
			std::map<int, std::string> status;
			status[100] = "Continue";
			status[101] = "Switching Protocols";
			status[102] = "Processing";
			status[103] = "Early Hints";
			status[200] = "OK";
			status[201] = "Created";
			status[202] = "Accepted";
			status[203] = "Non-Authoritative Information";
			status[204] = "No Content";
			status[205] = "Reset Content";
			status[206] = "Partial Content";
			status[207] = "Multi-Status";
			status[208] = "Already Reported";
			status[226] = "IM Used";
			status[300] = "Multiple Choices";
			status[301] = "Moved Permanently";
			status[302] = "Found";
			status[303] = "See Other";
			status[304] = "Not Modified";
			status[305] = "Use Proxy";
			status[306] = "Switch Proxy";
			status[307] = "Temporary Redirect";
			status[308] = "Permanent Redirect";
			status[400] = "Bad Request";
			status[401] = "Unauthorized";
			status[402] = "Payment Required";
			status[403] = "Forbidden";
			status[404] = "Not Found";
			status[405] = "Method Not Allowed";
			status[406] = "Not Acceptable";
			status[407] = "Proxy Authentication Required";
			status[408] = "Request Timeout";
			status[409] = "Conflict";
			status[410] = "Gone";
			status[411] = "Length Required";
			status[412] = "Precondition Failed";
			status[413] = "Payload Too Large";
			status[414] = "URI Too Long";
			status[415] = "Unsupported Media Type";
			status[416] = "Range Not Satisfiable";
			status[417] = "Expectation Failed";
			status[418] = "I\'m a teapot"; 
			status[421] = "Misdirected Request";
			status[422] = "Unprocessable Entity";
			status[423] = "Locked";
			status[424] = "Failed Dependency";
			status[425] = "Too Early";
			status[426] = "Upgrade Required";
			status[428] = "Precondition Required";
			status[429] = "Too Many Requests";
			status[431] = "Request Header Fields Too Large";
			status[451] = "Unavailable For Legal Reasons";
			status[500] = "Internal Server Error";
			status[501] = "Not Implemented";
			status[502] = "Bad Gateway";
			status[503] = "Service Unavailable";
			status[504] = "Gateway Timeout";
			status[505] = "HTTP Version Not Supported";
			status[506] = "Variant Also Negotiates";
			status[507] = "Insufficient Storage";
			status[508] = "Loop Detected";
			status[510] = "Not Extended";
			status[511] = "Network Authentication Required";

			return status;
		}

std::map<std::string, std::string> HTTPResponse::init_content_type()
{
			// https://www.geeksforgeeks.org/http-headers-content-type/
			std::map<std::string, std::string> type;
			type["gif"] = "image/gif";
			type["jpg"] = "image/jpeg";
			type["jpeg"] = "image/jpeg";
			type["png"] = "image/png";
			type["css"] = "text/css";
			type["html"] = "text/html";
			type["javascript"] = "text/javascript";
			
			return type;
}

std::string HTTPResponse::get_default_error_page(status_code error_code)
{
	// todo
	std::string msg; // write the content of html file

	msg += std::to_string(error_code) + " " + _status_line[error_code] + "\r\n";
	
	std::string file;
	file = "HTTP/1.1 " + std::to_string(error_code) + " " + _status_line[error_code] + "\r\n";
	file += "Content-Type: text/html\r\nContent-Length: " + std::to_string(msg.size()) + "\r\n\n" + msg;

	return file;
}

HTTPResponse::HTTPResponse(std::string const &HTTP_version, std::string const &method, std::string const &file_uri, Location_behavior behavior, status_code status) : _HTTP_version(HTTP_version), _status_code(status), _file_uri(file_uri)
{
	if (behavior == existed_file)
	{
		if (method == "GET")
		{
			std::map<std::string, std::string>::iterator file_type_iterator = _content_type.find(get_file_type(file_uri));
			if (directory_exist(get_file_uri())) // want to read a file, but it's a directory
				throw(Forbidden);
			if (!uri_exist(get_file_uri()))
				throw(NotFound);
			if (file_type_iterator == _content_type.end())
				throw(UnsupportedMediaType);
			std::string const &content = get_file_content(get_file_uri());
			
			if (content.size() == 0)
				set_status_code(NoContent);
			else
				set_status_code(OK);;

			_msg = "HTTP/" + get_HTTP_version() + " " + std::to_string(get_status_code()) + " " + _status_line[get_status_code()] + "\r\n";
			_msg += "Content-Type: " + file_type_iterator->second + "\r\nContent-Length:" + std::to_string(content.size()) + "\r\n\n" + content;
		}
		else if (method == "POST")
		{
			// todo	
		}
		else if (method == "DELETE")
		{
			// todo
		}
		else
		{
			// todo ?
		}
	}
	else if (behavior == redirect)
	{
		// source : https://developer.mozilla.org/en-US/docs/Web/HTTP/Redirections
		set_status_code(MovedPermanently);
		
		_msg = "HTTP/" + get_HTTP_version() + " " + std::to_string(get_status_code()) + " " + _status_line[get_status_code()] + "\r\n";
		_msg += "Location: " + get_file_uri();
	}
	else if (behavior == autoindex)
	{
		if (!directory_exist(get_file_uri()))
			throw(NotFound);
		Autoindex file(get_file_uri());
		
		set_status_code(OK);
		_msg = "HTTP/" + get_HTTP_version() + " " + std::to_string(get_status_code()) + " " + _status_line[get_status_code()] + "\r\n";
		_msg += "Content-Type: text/html\r\nContent-Length:" + std::to_string(file.get_html().size()) + "\r\n\n" + file.get_html();

	}
	else
	{
		// todo
	}
}

void HTTPResponse::send_error_page(int fd, std::string const &error_pages_root, status_code error_code)
{
	try
	{
		HTTPResponse response("1.1", "GET", error_pages_root + "/" + std::to_string(error_code) + ".html", existed_file, error_code);
		write(fd, response.get_msg().c_str(), response.get_msg().size());
		// std::cerr << response.get_msg() << std::endl;
	}
	catch (status_code status)
	{
		if (status != NotFound)
		{
			print_log("WTF?? Something wrong in srcs/http/HTTPResponse.cpp : send_error_page()\n");
			exit(EXIT_FAILURE);
		}
		write(fd, get_default_error_page(error_code).c_str(), get_default_error_page(error_code).size());
		// std::cerr << get_default_error_page(error_code) << std::endl;
	}
}
