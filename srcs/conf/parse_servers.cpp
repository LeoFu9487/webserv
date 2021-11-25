/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_servers.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:13:08 by xli               #+#    #+#             */
/*   Updated: 2021/11/25 10:47:20 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "conf.hpp"
#include "ServerInfo.hpp"

// fill the vector result
// if any error, throw an exception (check the file includes/exception.hpp)

void parse_servers(std::vector<ServerInfo> &result, char *conf_file_path)
{
	(void)result;
	if (!conf_file_path)
		throw(InvalidConfFilePath());
	std::ifstream	file;
	file.open(conf_file_path);
	if (!file)
		throw(InvalidConfFile());
	char	c;
	std::string	str;
	while (file.get(c))
		str.push_back(c);
	file.close();
	//std::cout << str << std::endl;
	if (valid_bracket(str) == false)
		throw(ConfFileParseError("Invalid numbers bracket"));
	if (!str.compare(0, 8, "server {"))
	{
		//std::cout << "IN1";
		ServerInfo	new_server;
		std::string	line;
		line = get_line(str, 0);
		if (nb_tokens(line.c_str()) != 2)
			throw(ConfFileParseError("Invalid server header"));
		int	ct = 1;
		while (ct < nb_lines(str))
		{
			//std::cout << "IN2";
			line = get_line(str, ct);
			if (!line.compare(0, 7, "listen "))
				new_server.set_server(PORT, 7, line);
			else if (!line.compare(0, 12, "server_name "))
				new_server.set_server(NAME, 12, line);
			else if (!line.compare(0, 11, "error_page "))
				new_server.set_server(ERROR, 11, line);
			else if (!line.compare(0, 9, "max_size "))
				new_server.set_server(SIZE, 9, line);
			else if (!line.compare(0, 9, "location "))
			{
				if (nb_tokens(line.c_str()) != 3)
					throw(ConfFileParseError("Invalid location header"));
				new_location(new_server, str, ct);
			}
			// else
			// 	throw(ConfFileParseError());
			ct++;
		}
	}
}

/*
** Parsing and filling location info
*/

void new_location(ServerInfo &n_server, std::string &str, int &ct)
{
	Location	n_location(n_server.get_port());
	std::string	line;
	while (ct < nb_lines(str))
	{
		line = get_line(str, ct);
		if (!line.compare(0, 10, "autoindex "))
			n_location.set_location(AUTOINDEX, 10, line);
		else if (!line.compare(0, 6, "index "))
			n_location.set_location(INDEX, 6, line);
		else if (!line.compare(0, 5, "root "))
			n_location.set_location(ROOT, 5, line);
		else if (!line.compare(0, 13, "allow_method "))
			n_location.set_location(METHOD, 13, line);
		ct++;
	}
}

/*
** Varify if bracket are alway in pairs
*/

bool valid_bracket(std::string str)
{
	std::stack<char>	bracket;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '{')
			bracket.push(str[i]);
		if (str[i] == '}')
		{
			if (bracket.empty() || bracket.top() != '{')
				return false;
			if (!bracket.empty() && bracket.top() == '{')
				bracket.pop();
		}

	}
	if (bracket.empty())
		return true;
	return false;
}

/*
**	listen 8080
**	server_name localhost
**	root www
**	error_page 404.html
**	max_size 10m
*/

/*
** Get total number of lines of the string
*/

int nb_lines(std::string str)
{
	int	i;
	int	lines;

	i = 0;
	lines = 1;
	while (str[i])
	{
		if (str[i++] == '\n')
			++lines;
	}
	return lines;
}

/*
** Get n-th line of string
*/

std::string get_line(std::string str, int n)
{
	int	i;
	int	j;
	int	ct;

	if (n >= nb_lines(str))
		return std::string();
	i = 0;
	ct = 0;
	while (ct < n)
	{
		if (str[i++] == '\n')
			++ct;
	}
	while (std::isspace(str[i]) && str[i] != '\n')
		++i;
	j = 0;
	while (str[i + j] && str[i + j] != '\n')
		++j;
	while (j > 0 && std::isspace(str[i + j - 1]))
		--j;
	return (std::string(str, i, j));
}

/*
** Get numbers of tokens of string
*/

int nb_tokens(const char *str)
{
	int ct = 0;
	int res = 0;
	while (str[ct] != '\0')
	{
		while (isspace(str[ct]))
			ct++;
		int tmp = ct;
		while (isalnum(str[ct]) || ispunct(str[ct]))
			ct++;
		if (tmp != ct)
			res++;
	}
	return res;
}
