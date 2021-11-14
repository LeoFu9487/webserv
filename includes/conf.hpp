#pragma once
#include "webserv.hpp"

class ServerInfo;

void parse_servers(std::vector<ServerInfo> &result, char *conf_file_path);
