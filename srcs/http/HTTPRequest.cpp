#include "../../includes/webserv.hpp"


HTTPRequest::HTTPRequest(std::string const &request):_behavior(none),_file_uri("") // throw status_code if error
{
	std::stringstream	ss(request);

	if (!(ss >> _method))
		throw(BadRequest);
	if (!(ss >> _path))
		throw(BadRequest);
	if (!(ss >> _HTTP_version))
		throw(BadRequest);
}

static bool find_file(HTTPRequest &request, Location const &location, std::string path)
{
	std::string uri = location.get_uri();
	
	if (path.size() < uri.size() || path.substr(0, uri.size()) != uri ||
	(path.size() > uri.size() && path[uri.size()] != '/' && path[uri.size() - 1] != '/') )
		return false;

	// redirect

	if (location.get_redirect() != "")
	{
		request.set_file_uri(path.replace(0, uri.size(), location.get_redirect()));
		request.set_behavior(redirect);
		return true;
	}

	std::string	root = location.get_root();
	if (root == "" || !directory_exist(root))
		return false;
	

	if (path.size() <= uri.size() + 1) // path == location_uri or path == location_uri + 1
	{
		// index or autoindex
		if (location.get_autoindex())
		{
			request.set_file_uri(root);
			request.set_behavior(autoindex);
			return true;
		}
		std::string index_path = location.get_index();
		if (index_path != "")
		{
			if (root[root.size() - 1] != '/' && index_path[0] != '/')
				index_path = root + "/" + index_path;
			else
				index_path = root + index_path;
			if (file_exist(index_path))
			{
				request.set_file_uri(index_path);
				request.set_behavior(existed_file);
				return true;
			}
		}
	}
	
	if (uri[uri.size() - 1] == '/' && root[root.size() - 1] != '/')
		root += "/";
	path.replace(0, uri.size(), root);

	if (file_exist(path))
	{
		request.set_file_uri(path);
		request.set_behavior(existed_file);
		return true;
	}
	return false;
}

void	HTTPRequest::check_request(ServerInfo const &server)
{
	// check version
	if (_HTTP_version != "HTTP/1.0" && _HTTP_version != "HTTP/1.1")
		throw(HTTPVersionNotSupported);
	
	// check path
	std::vector<Location>::const_iterator it;

	for (it = server.get_location().begin() ; it != server.get_location().end() ; ++it)
		if (find_file(*this, *it, _path))
		{
			// std::cerr << it->get_uri() << std::endl << std::endl;
			break ;
		}

	if (it == server.get_location().end())
	{
		// std::cerr << "JAJAJA\n";
		throw(NotFound);
	}
	
	// check method
	
	std::vector<std::string> const &allow_method = it->get_allow_method();
	for (size_t i = 0 ; i < allow_method.size() ; ++i)
		if (_method == allow_method[i])
			return ;
	
	throw(MethodNotAllowed);
}

void	HTTPRequest::set_behavior(Location_behavior behavior)
{
	_behavior = behavior;
}

void	HTTPRequest::set_file_uri(std::string const &file_uri)
{
	_file_uri = file_uri;
}

Location_behavior	HTTPRequest::get_behavior() const
{
	return _behavior;
}

std::string const &HTTPRequest::get_method() const
{
	return _method;
}

std::string const &HTTPRequest::get_file_uri() const
{
	return _file_uri;
}

std::string const &HTTPRequest::get_HTTP_versoin() const
{
	return _HTTP_version;
}

void	HTTPRequest::print() const
{
	std::cerr	<< "HTTP Request attributes :\n"
				<< "file_uri : " << get_file_uri() <<"\n"
				<< "behavior : " << get_behavior() << "\n\n";
}
