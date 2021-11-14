#pragma once
#include "webserv.hpp"


void	start_server(std::map<int, ServerInfo *> &fd_of_servers);
void	close_sockets(std::map<int, ServerInfo *> &fd_of_servers);

#ifdef __linux__

void	add_read_event_in_epoll(int epoll_fd, int socket_fd);
int	create_epoll(std::map<int, ServerInfo *> &fd_of_servers);

#elif

#endif
