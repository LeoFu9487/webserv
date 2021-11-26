#include "../../includes/webserv.hpp"


HTTPRequest::HTTPRequest(std::string const &request):_location(NULL) // throw status_code if error
{
	std::stringstream	ss(request);

	if (!(ss >> _method))
		throw(MethodNotAllowed);
	if (!(ss >> _path))
		throw(NotFound);
	if (!(ss >> _HTTP_version))
		throw(HTTPVersionNotSupported);
}

static bool find_file(Location const &location, std::string const &path)
{
	// todo
	// std::ifstream infile(fileName);
    // return infile.good();
	
	std::string uri = location.get_uri();
	if (path.size() < uri.size() || path.substr(0, uri.size()) != uri ||
	(path.size() > uri.size() && path[uri.size()] != '/') )
		return false;
	
	// if (location.get_redirect())
	// 	return true;

	if (path.size() == uri.size() || path.size() + 1 == uri.size())
	{
		
	}
	/*
	autoindex
	redirect
	root
	index
	*/

	return false;
}

void	HTTPRequest::check_request(ServerInfo const &server)
{
	if (_HTTP_version != "HTTP/1.0" && _HTTP_version != "HTTP/1.1")
		throw(HTTPVersionNotSupported);
	
	// check path
	std::vector<Location>::const_iterator it;
	for (it = server.get_location().begin() ; it != server.get_location().end() ; ++it)
		if (find_file(*it, _path))
		{
			this->set_location(*it);
			break ;
		}
	
	if (it == server.get_location().end())
		throw(NotFound);

	
	// check method
	
	std::vector<std::string> const &allow_method = it->get_allow_method();
	for (size_t i = 0 ; i < allow_method.size() ; ++i)
		if (_method == allow_method[i])
			return ;
	
	throw(MethodNotAllowed);
}

void	HTTPRequest::set_location(Location const &location)
{
	_location = &location;
}

Location const	*HTTPRequest::get_location() const
{
	return _location;
}
