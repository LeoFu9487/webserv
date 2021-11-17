/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:01:26 by xli               #+#    #+#             */
/*   Updated: 2021/11/16 17:20:44 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "webserv.hpp"
#include <iostream>

class ServerInfo
{
	private:
		int			_port;
		std::string	_server_names;
		std::string	_error_pages;
		int			_maxClient;

	public:
		void	print() const;

		ServerInfo();
		ServerInfo(const ServerInfo &copy);
		ServerInfo operator=(const ServerInfo &copy);
		~ServerInfo();

		int					getPort() const;
		std::string const	&getErrorPage() const;
		int					getMaxClient() const;
		void				setPort();
		void				setErrorPage();
		void				setMaxClient();
};

/*
Fill the attributes that can be indicated in conf file

getters for all the attributes

public method :
	print :
		print all the attributes via std::cerr, output must be readable

*/
