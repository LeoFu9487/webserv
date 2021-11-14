#pragma once
#include "webserv.hpp"

class ServerInfo
{
	private:
		int			_port;
		std::string	_IP;
		int			_max_client;

	public:
		void	print() const;
		ServerInfo();

		int					get_port() const;
		std::string const	&get_IP() const;
		int					get_max_client() const;
};

/*
Fill the attributes that can be indicated in conf file

getters for all the attributes

public method :
	print :
		print all the attributes via std::cerr, output must be readable

*/