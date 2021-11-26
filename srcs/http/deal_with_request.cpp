#include "webserv.hpp"

void	deal_with_request(std::map<int, ClientInfo>::iterator it)
{
	// after parsing the request, send it to client_fd
	try
	{
		HTTPRequest	request(it->second.get_request());
		request.check_request(it->second.get_server()); // todo : find_file in HTTPRequest.cpp
		request.print();
	}
	catch(status_code error_code)
	{
		// deal with error
		std::cerr << "error : " << error_code << "\n";
	}
	
	// std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length:15\n\n<img src=\"sun\">";
	// std::cerr << it->second.get_request() <<"\n";
	// write(it->first, hello.c_str() , hello.size());
}
