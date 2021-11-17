/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:01:04 by xli               #+#    #+#             */
/*   Updated: 2021/11/17 09:21:05 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerInfo.hpp"

ServerInfo::ServerInfo() : _port(0), _max_client(0) {}
ServerInfo::ServerInfo(const ServerInfo &copy)
:	_port(copy._port),
	_error_page(copy._error_page),
	_max_client(copy._max_client) {}
ServerInfo &ServerInfo::operator=(const ServerInfo &copy)
{
	ServerInfo	tmp(copy);
	std::swap(tmp, *this);
	return (*this);
}
ServerInfo::~ServerInfo() {}

int	ServerInfo::get_port() const
{
	return _port;
}

std::string const	&ServerInfo::get_error_page() const
{
	return _error_page;
}

int	ServerInfo::getMaxClient() const
{
	return _max_client;
}

#ifdef TEST
ServerInfo::ServerInfo()
{
	_port = 8080;
	_IP = "0.0.0.0";
	_maxClient = 100;
}
#endif
