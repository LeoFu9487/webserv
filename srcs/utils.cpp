#include "webserv.hpp"

void	print_log(std::string const &msg)
{
	std::cerr << msg <<"\n";
}

void	make_socket_nonblock(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
		throw(FailToGetFdStatus());
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw(FailToSetFdStatus());
}


bool	directory_exist(std::string const &dir)
{
    DIR *pDir;
    bool bExists = false;

    pDir = opendir (dir.c_str());

    if (pDir != NULL)
    {
        bExists = true;    
        (void) closedir (pDir);
    }

    return bExists;
}

bool	file_exist(std::string const &file)
{
    std::ifstream is(file.c_str());
    if (!is)
        return false;
    return true;
}
