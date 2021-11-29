#include "webserv.hpp"

void	deal_with_request(std::map<int, ClientInfo>::iterator it)
{
	// after parsing the request, send it to client_fd
	try
	{
		// std::cerr << it->second.get_request() << std::endl;
		HTTPRequest	request(it->second.get_request());
		
		request.check_request(it->second.get_server());
		
		HTTPResponse response(request.get_HTTP_versoin(), request.get_method(), request.get_file_uri(), request.get_behavior());
		write(it->first, response.get_msg().c_str(), response.get_msg().size());
		print_log("Respond with HTTP status : " + std::to_string(response.get_status_code()) + " " + HTTPResponse::_status_line[response.get_status_code()]);
	}
	catch(status_code error_code)
	{
		HTTPResponse::send_error_page(it->first, it->second.get_server().get_error(), error_code);
		print_log("Respond with HTTP status : " + std::to_string(error_code) + " " + HTTPResponse::_status_line[error_code]);
	}
	
	// std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length:15\n\n<img src=\"sun\">";
	// std::cerr << it->second.get_request() <<"\n";
	// write(it->first, hello.c_str() , hello.size());
}
