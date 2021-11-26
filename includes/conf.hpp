/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:13:31 by xli               #+#    #+#             */
/*   Updated: 2021/11/26 18:22:04 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "webserv.hpp"
#include <iostream>
#include <fstream>

class ServerInfo;

enum e_server
{
	PORT,
	NAME,
	ERROR,
	SIZE,
};

enum e_location
{
	URI,
	AUTOINDEX,
	INDEX,
	ROOT,
	REDIRECT,
	METHOD,
	UPLOADPATH,
	CGI
};

bool		valid_bracket(std::string str);
int			nb_lines(std::string str);
std::string get_line(std::string str, int n);
int			nb_tokens(const char *);
void		new_location(ServerInfo &n_server, std::string &str, int &ct);
void		parse_servers(std::vector<ServerInfo> &result, char *conf_file_path);
