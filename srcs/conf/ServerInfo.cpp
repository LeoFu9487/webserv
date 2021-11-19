/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:01:04 by xli               #+#    #+#             */
/*   Updated: 2021/11/19 16:28:18 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerInfo.hpp"

ServerInfo::ServerInfo() : _port(0), _max_client(0) {}

ServerInfo::ServerInfo(const ServerInfo &copy)
:	_port(copy._port),
	_server_names(copy._server_names),
	_root(copy._root),
	_IP(copy._IP),
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

int ServerInfo::get_port() const { return _port; }

std::vector<std::string> ServerInfo::get_names() const { return _server_names; }

std::string ServerInfo::get_root() const { return _root; }

std::string ServerInfo::get_IP() const { return _IP; }

std::string ServerInfo::get_error() const { return _error_pages; }

int ServerInfo::get_max_client() const { return _max_client; }


/*
** =============== SETTER ===============
*/

void ServerInfo::set_server(int index, const int &pos, const std::string &str)
{
	func	funcs[] = {&ServerInfo::set_port/*, &ServerInfo::set_names,
		&ServerInfo::set_root, &ServerInfo::set_error, &ServerInfo::set_max_client*/};

	//tmp = str[pos]?
	const char *tmp = str.c_str() + pos;
	int i = 0;
	while (isspace(tmp[i]))
		i++;
	//eg. for listen 8080, tmp + i = 8080
	(this->*(funcs[index]))(tmp + i);
}

//Need to parse 8080 1 or not?

void ServerInfo::set_port(const char *p)
{
	//std::cout << "p = " << p << std::endl;
	std::string	tmp = p;
	tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());
	for (size_t i = 0; i < tmp.size(); i++)
		if (tmp[i] < 48 || tmp[i] > 57)
			throw(ConfFileParseError());

	_port = atoi(p);
	std::cout << "p = " << _port << std::endl;
}




// #ifdef TEST
// ServerInfo::ServerInfo()
// {
// 	_port = 8080;
// 	_host = "0.0.0.0";
// 	_max_client = 100;
// }
// #endif
