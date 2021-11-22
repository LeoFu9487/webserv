/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:01:04 by xli               #+#    #+#             */
/*   Updated: 2021/11/22 14:18:22 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerInfo.hpp"

ServerInfo::ServerInfo() : _port(0), _max_client(0) {}

ServerInfo::ServerInfo(const ServerInfo &copy)
:	_port(copy._port),
	_server_name(copy._server_name),
	_IP(copy._IP),
	_error_pages(copy._error_pages),
	_max_client(copy._max_client),
	_allow_method(copy._allow_method),
	_root(copy._root) {}

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

std::string ServerInfo::get_name() const { return _server_name; }

std::string ServerInfo::get_root() const { return _root; }

std::string ServerInfo::get_IP() const { return _IP; }

std::string ServerInfo::get_error() const { return _error_pages; }

int ServerInfo::get_max_client() const { return _max_client; }


/*
** =============== SETTER ===============
*/

void ServerInfo::set_server(int index, const int &pos, const std::string &str)
{
	typedef void (ServerInfo::*func)(const char *);
	func	funcs[] = {&ServerInfo::set_port, &ServerInfo::set_name,
		&ServerInfo::set_IP, &ServerInfo::set_error, &ServerInfo::set_max_client};

	//tmp = str[pos]?
	// std::cout << "str = " << str << std::endl;
	const char *tmp = str.c_str() + pos;
	// std::cout << "tmp = " << tmp << std::endl;
	int i = 0;
	while (isspace(tmp[i]))
		i++;
	//eg. for listen 8080, tmp + i = 8080
	(this->*funcs[index])(tmp + i);
}

void ServerInfo::set_port(const char *p)
{
	if (nb_tokens(p) != 1)
		throw(ConfFileParseError("put only one port to listen"));
	std::string	tmp = p;
	tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());
	for (size_t i = 0; i < tmp.size(); i++)
		if (tmp[i] < 48 || tmp[i] > 57)
			throw(ConfFileParseError("put only digits for port"));
	_port = atoi(p);
	// std::cout << "_port = " << _port << std::endl;
}

//server_name one or multiple(from string to vector?)
void ServerInfo::set_name(const char *n)
{
	if (nb_tokens(n) != 1)
		throw(ConfFileParseError("put only one server name"));
	std::string tmp = n;
	tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());
	_server_name = tmp;
	// std::cout << "_server_name = " << _server_name << std::endl;
}

void ServerInfo::set_IP(const char *i) { _IP = i; }

void ServerInfo::set_error(const char *e)
{
	if (nb_tokens(e) != 1)
		throw(ConfFileParseError("put only one error path"));
	_error_pages = e;
	// std::cout << "_error_pages = " << _error_pages << std::endl;
}

//max_size accept 10m or just 10?
void ServerInfo::set_max_client(const char *s)
{
	if (nb_tokens(s) != 1)
		throw(ConfFileParseError("put only one max client body size"));
	std::string	tmp = s;
	tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());
	for (size_t i = 0; i < tmp.size(); i++)
		if (tmp[i] < 48 || tmp[i] > 57)
			throw(ConfFileParseError("put only digits for max client body size"));
	_port = atoi(s);
	// std::cout << "_port = " << _port << std::endl;
}

// void ServerInfo::set_root(const char *r)
// {
// 	if (nb_tokens(r) != 1)
// 		throw(ConfFileParseError());
// 	std::string	tmp = r;
// 	tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());
// 	_root = tmp;
// 	// std::cout << "_root = " << _root << std::endl;
// }


// #ifdef TEST
// ServerInfo::ServerInfo()
// {
// 	_port = 8080;
// 	_host = "0.0.0.0";
// 	_max_client = 100;
// }
// #endif
