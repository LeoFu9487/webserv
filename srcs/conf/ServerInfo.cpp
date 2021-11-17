/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:01:04 by xli               #+#    #+#             */
/*   Updated: 2021/11/16 17:17:49 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerInfo.hpp"

ServerInfo::ServerInfo() : _port(0), _maxClient(0) {}
ServerInfo::ServerInfo(const ServerInfo &copy)
:	_port(copy._port),
	_errorPage(copy._errorPage),
	_maxClient(copy._maxClient) {}
ServerInfo &ServerInfo::operator=(const ServerInfo &copy)
{
	ServerInfo	tmp(copy);
	std::swap(tmp, *this);
	return (*this);
}
ServerInfo::~ServerInfo() {}

int	ServerInfo::getPort() const
{
	return _port;
}

std::string const	&ServerInfo::getErrorPage() const
{
	return _errorPage;
}

int	ServerInfo::getMaxClient() const
{
	return _maxClient;
}

#ifdef TEST
ServerInfo::ServerInfo()
{
	_port = 8080;
	_IP = "0.0.0.0";
	_maxClient = 100;
}
#endif
