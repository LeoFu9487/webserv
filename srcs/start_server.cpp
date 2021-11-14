#include "../includes/webserv.hpp"

#ifdef __linux__

void	start_server(std::map<int, ServerInfo *> &fd_of_servers)
{
	int	epoll_fd = create_epoll(fd_of_servers);
	(void)epoll_fd;
}

#else

#endif
