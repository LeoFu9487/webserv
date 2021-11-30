#include "webserv.hpp"

void print_log(std::string const &msg)
{
    std::cerr << msg << "\n";
}

void make_socket_nonblock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        throw(FailToGetFdStatus());
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
        throw(FailToSetFdStatus());
}

bool directory_exist(std::string const &dir)
{
    DIR *pDir;
    bool bExists = false;

    pDir = opendir(dir.c_str());

    if (pDir != NULL)
    {
        bExists = true;
        (void)closedir(pDir);
    }

    return bExists;
}

bool uri_exist(std::string const &file)
{
    std::ifstream is(file.c_str());
    if (!is)
        return false;
    return true;
}

std::string get_file_type(std::string const &file_uri)
{
    size_t dot = file_uri.find_last_of(".");

    if (dot == std::string::npos)
        return "";
    return file_uri.substr(dot + 1);
}

std::string get_file_content(std::string const &content)
{
    std::ifstream input_file(content.c_str());
    if (!input_file.is_open())
        throw(UnsupportedMediaType); // todo : check ?

    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

std::string file_or_directory(std::string const &uri)
{
    return directory_exist(uri) ? "Directory" : "File";
}

std::string std::to_string(int n)
{
    ostringstream convert;
    convert << n;
    return convert.str();
}

std::string std::to_string(size_t n)
{
    ostringstream convert;
    convert << n;
    return convert.str();
}
