#include "webserv.hpp"

void	deal_with_request(std::map<int, ClientInfo>::iterator it)
{
	// after parsing the request, send it to client_fd
	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length:15\n\n<img src=\"sun\">";
	std::cerr << it->second.get_request() <<"\n";
	write(it->first, hello.c_str() , hello.size());
}
