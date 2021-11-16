#include "../includes/webserv.hpp"

#ifdef __linux__

void	start_server(std::map<int, ServerInfo *> &fd_of_servers)
{
	int	epoll_fd = create_epoll(fd_of_servers);
	struct epoll_event	eventlist[MAX_EVENTS];
	std::map<int, ClientInfo> fd_of_clients;

	for (;;) // infinite loop for new event
	{
		int event_amount = epoll_wait(epoll_fd, eventlist, MAX_EVENTS, -1);
		if (event_amount == -1)
			throw(FailToWaitEpoll());
		for (int i = 0 ; i < event_amount ; ++i)
		{
			if ((eventlist[i].events & EPOLLRDHUP)
				|| (eventlist[i].events & EPOLLHUP)
				|| (eventlist[i].events & EPOLLERR)) // client quit
				delete_client_from_epoll(fd_of_clients, epoll_fd, eventlist[i].data.fd);
			else if (fd_of_servers.find(eventlist[i].data.fd) != fd_of_servers.end()) // event of server means new client connected
				accept_new_client(epoll_fd, eventlist[i].data.fd, fd_of_clients);
			else if (eventlist[i].events & EPOLLIN) // there is new input from old client
			{
				std::map<int, ClientInfo>::iterator it = fd_of_clients.find(eventlist[i].data.fd);
				if (it == fd_of_clients.end())
					throw(ClientNotInMap());
				if (read_request(it) <= 0)
					delete_client_from_epoll(fd_of_clients, epoll_fd, eventlist[i].data.fd);
				else
				{
					#ifdef TEST
						std::cerr << it->second.get_request() <<"\n";
					#endif
					//respond to client
				}
			}
		}
	}
}

#else

#endif
