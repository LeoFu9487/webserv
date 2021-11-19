/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:01:26 by xli               #+#    #+#             */
/*   Updated: 2021/11/19 09:55:42 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "webserv.hpp"
#include <iostream>
#include <vector>
#include <string>

class ServerInfo
{
	private:
		int							_port;
		std::vector<std::string>	_server_names;
		std::string					_root;
		std::string					_IP;
		std::string					_error_pages;
		int							_max_client;

	public:
		void	print() const;

		ServerInfo();
		ServerInfo(const ServerInfo &copy);
		ServerInfo &operator=(const ServerInfo &copy);
		~ServerInfo();

		int							get_port() const;
		std::vector<std::string>	get_names() const;
		std::string					get_root() const;
		std::string					get_IP() const;
		std::string					get_error() const;
		int							get_max_client() const;

		void						set_server(int index, const int &pos, const std::string &str);
		void						set_port(const char *);
		// void						set_names(const char *);
		// void						set_root(const char *);
		// void						set_IP(const char *);
		// void						set_error(const char *);
		// void						set_max_client(const char *);
};

typedef void (ServerInfo::*func)(const char *);

/*
Fill the attributes that can be indicated in conf file

getters for all the attributes

public method :
	print :
		print all the attributes via std::cerr, output must be readable

*/
