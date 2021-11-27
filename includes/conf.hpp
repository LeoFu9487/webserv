/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:13:31 by xli               #+#    #+#             */
/*   Updated: 2021/11/27 16:23:42 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "webserv.hpp"
#include <iostream>
#include <fstream>
#include <stack>

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
int			closing_bracket(std::string str, int pos);
int			nb_lines(std::string str);
std::string get_line(std::string str, int n);
int			nb_tokens(const char *);
void		new_server(std::string &str, int &pos);
void		new_location(ServerInfo &n_server, std::string &str, int &ct);
void		parse_servers(std::vector<ServerInfo> &result, char *conf_file_path);
