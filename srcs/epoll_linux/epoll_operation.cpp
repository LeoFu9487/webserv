#ifdef __linux__
# include "../../includes/webserv.hpp"

int	create_epoll(std::map<int, ServerInfo *> &fd_of_servers)
{
	int epoll_fd = epoll_create(1);
	if (epoll_fd == -1)
		throw(FailToCreateEpoll());
	for (std::map<int, ServerInfo *>::iterator it = fd_of_servers.begin() ; it != fd_of_servers.end() ; ++it)
		add_read_event_in_epoll(epoll_fd, it->first);
	return (epoll_fd);
}

void	add_read_event_in_epoll(int epoll_fd, int socket_fd)
{
	struct epoll_event	changelist;

	std::memset(&changelist, 0, sizeof(changelist));
	changelist.events = EPOLLIN;
	changelist.data.fd = socket_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &changelist) == -1)
		throw(FailToControlEpoll());
}

#endif