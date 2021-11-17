/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:01:26 by xli               #+#    #+#             */
/*   Updated: 2021/11/17 09:22:49 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "webserv.hpp"
#include <iostream>

class ServerInfo
{
	private:
		int			_port;
		std::string	_IP;
		std::string	_error_pages;
		int			_max_client;

	public:
		void	print() const;

		ServerInfo();
		ServerInfo(const ServerInfo &copy);
		ServerInfo operator=(const ServerInfo &copy);
		~ServerInfo();

		int					get_ort() const;
		std::string const	&get_IP() const;
		std::string const	&get_error_page() const;
		int					getMaxClient() const;
		void				set_port();
		void				set_error_page();
		void				set_max_client();
};

/*
Fill the attributes that can be indicated in conf file

getters for all the attributes

public method :
	print :
		print all the attributes via std::cerr, output must be readable

*/
