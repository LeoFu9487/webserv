#pragma once
#include "webserv.hpp"

void	print_log(std::string const &msg);
void	make_socket_nonblock(int fd);
bool	directory_exist(std::string const &dir);
bool	file_exist(std::string const &file);
