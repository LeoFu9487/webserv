#pragma once
#include "webserv.hpp"
class ClientInfo
{
	private:
		std::string _request;


	public:
		ClientInfo();

		void	set_request(char *, ssize_t);

		std::string const &get_request() const;
};