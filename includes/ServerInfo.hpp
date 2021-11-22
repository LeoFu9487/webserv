/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:01:26 by xli               #+#    #+#             */
/*   Updated: 2021/11/22 18:51:10 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "webserv.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class ServerInfo
{
	private:
		/*
		** Server attributes
		*/
		int							_port;
		std::string					_server_name;
		std::string					_IP;
		std::string					_error_pages;
		int							_max_client;

		/*
		** Location attributes
		*/
		bool						_autoindex;
		std::string					_index;
		std::string					_root;
		std::vector<std::string>	_allow_method;

	public:
		void	print() const;

		ServerInfo();
		ServerInfo(const ServerInfo &copy);
		ServerInfo &operator=(const ServerInfo &copy);
		~ServerInfo();

		/*
		** Server getters
		*/
		int							get_port() const;
		std::string					get_name() const;
		std::string					get_IP() const;
		std::string					get_error() const;
		int							get_max_client() const;

		/*
		** Location getters
		*/
		bool						get_autoindex() const;
		std::string					get_index() const;
		std::vector<std::string>	get_allow_method() const;
		std::string					get_root() const;

		void						set_server(int index, const int &pos, const std::string &str);
		void						set_location(int index, const int &pos, const std::string &str);

	private:
		/*
		** Server setters
		*/
		void						set_port(const char *);
		void						set_name(const char *);
		void						set_IP(const char *);
		void						set_error(const char *);
		void						set_max_client(const char *);

		/*
		** Location setters
		*/
		void						set_autoindex(const char *);
		void						set_index(const char *);
		void						set_allow_method(const char *);
		void						set_root(const char *);
};


/*
Fill the attributes that can be indicated in conf file

getters for all the attributes

public method :
	print :
		print all the attributes via std::cerr, output must be readable

*/
