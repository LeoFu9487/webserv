#include "../includes/webserv.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		print_log("Fatal : Incorrect Argument Amount");
		std::exit(EXIT_FAILURE);
	}

	std::vector<ServerInfo> serverlist;
	std::map<int, ServerInfo *> fd_of_servers;

	try
	{
		parse_servers(serverlist, av[1]);
		// #ifdef TEST
		// 	serverlist.push_back(ServerInfo());
		// #endif
		// create_listening_sockets(fd_of_servers, serverlist);
		// start_server(fd_of_servers);
		// // close_sockets(fd_of_servers); also close clients ?
	}
	catch(const std::exception& e)
	{
		print_log("Fatal : " + std::string(e.what()));
		std::exit(EXIT_FAILURE);
	}

	// while (1)
	// {
	// 	print_log("waiting for new connection");
	// 	int new_socket;
	// 	struct sockaddr_in address;
	// 	int addrlen;
	// 	if ((new_socket = accept(fd_of_servers.begin()->first, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
	// 	{
	// 		print_log("ERROR");
	// 		std::exit(EXIT_FAILURE);
	// 	}

	// 	char buffer[30000] = {0};
    //     read( new_socket , buffer, 30000);
    //     std::cerr << buffer  << "\n";

    //     close(new_socket);
	// }

	return (0);
}
