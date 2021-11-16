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
	struct epoll_event	event;

	std::memset(&event, 0, sizeof(event));
	event.events = EPOLLIN;
	event.data.fd = socket_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event) == -1)
		throw(FailToControlEpoll());
}

void	delete_client_from_epoll(std::map<int, ClientInfo> &fd_map, int epoll_fd, int target_fd)
{
	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, target_fd, NULL) == -1)
		throw(FailToControlEpoll());
	close(target_fd);
	fd_map.erase(target_fd);
}

void	accept_new_client(int epoll_fd, int server_fd, std::map<int, ClientInfo> &fd_of_clients)
{
	struct sockaddr_in	sockaddr;
	socklen_t	len = sizeof(sockaddr);
	ClientInfo	new_client;

	int client_fd = accept(server_fd, reinterpret_cast<struct sockaddr*>(&sockaddr), &len);
	if (client_fd < 0)
		throw(FailToAccept());
	add_read_event_in_epoll(epoll_fd, client_fd);
	/*
	todo : need to fill new client information
	*/
	fd_of_clients[client_fd] = new_client;
}

int	read_request(std::map<int, ClientInfo>::iterator it)
{
	char	buf[RCV_BUFFER_SIZE];
	ssize_t	len;

	len = recv(it->first, buf, RCV_BUFFER_SIZE - 1, 0);
	if (len > 0)
		it->second.set_request(buf, len);
	return len;
}

#endif