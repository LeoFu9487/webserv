#include "webserv.hpp"

// fill the vector result
// if any error, throw an exception (check the file includes/exception.hpp)

void parse_servers(std::vector<ServerInfo> &result, char *conf_file_path)
{
	(void)result;
	if (!conf_file_path)
		throw(InvalidConfFilePath());
}
