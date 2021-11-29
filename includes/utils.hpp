#pragma once
#include "webserv.hpp"

void	print_log(std::string const &msg);
void	make_socket_nonblock(int fd);
bool	directory_exist(std::string const &dir);
bool	file_exist(std::string const &file);
std::string get_file_type(std::string const &file);
std::string get_file_content(std::string const &content);


namespace  std
{
    std::string to_string(int n);
	std::string to_string(size_t n);
}

