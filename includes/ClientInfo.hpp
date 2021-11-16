#pragma once
#include "webserv.hpp"
class ClientInfo
{
	private:
		ServerInfo const	&_server;
		std::string			_request;

	public:
		ClientInfo(ServerInfo const &server);

		void	set_request(std::string const &str);

		std::string const &get_request() const;
		ServerInfo const &get_server() const;
};