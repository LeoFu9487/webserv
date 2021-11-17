/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:01:04 by xli               #+#    #+#             */
/*   Updated: 2021/11/17 11:10:47 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerInfo.hpp"

ServerInfo::ServerInfo() : _port(0), _max_client(0) {}

ServerInfo::ServerInfo(const ServerInfo &copy)
:	_port(copy._port),
	_server_names(copy._server_names),
	_host(copy._host),
	_error_pages(copy._error_pages),
	_max_client(copy._max_client) {}

ServerInfo &ServerInfo::operator=(const ServerInfo &copy)
{
	ServerInfo	tmp(copy);
	std::swap(tmp, *this);
	return (*this);
}
ServerInfo::~ServerInfo() {}

/*
** =============== GETTER ===============
*/

int const ServerInfo::get_port() const { return _port; }

std::vector<std::string> const &ServerInfo::get_names() const { return _server_names; }

std::string const &ServerInfo::get_host() const { return _host; }

std::string const &ServerInfo::get_error() const { return _error_pages; }

int const ServerInfo::get_max_client() const { return _max_client; }


/*
** =============== SETTER ===============
*/

void ServerInfo::set_port(const char *p)
{
	
	_port = atoi(p);
}




#ifdef TEST
ServerInfo::ServerInfo()
{
	_port = 8080;
	_host = "0.0.0.0";
	_max_client = 100;
}
#endif
