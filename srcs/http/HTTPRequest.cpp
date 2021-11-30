#include "../../includes/webserv.hpp"


HTTPRequest::HTTPRequest(std::string const &request):_behavior(none),_file_uri(""), _content_length(""), _content_type(""), _boundary(""), _accept("") // throw status_code if error
{
	std::stringstream	ss(request);

	if (!(ss >> _method))
		throw(BadRequest);
	if (!(ss >> _path))
		throw(BadRequest);
	if (!(ss >> _HTTP_version))
		throw(BadRequest);
	
	if (_method == "POST")
	{
		std::string tmp;
		while (ss >> tmp)
		{
			if (tmp == "Content-Length:")
			{
				if (_content_length == "")
					ss >> _content_length;
				else
					throw(BadRequest);
			}
			else if (tmp == "Content-Type:")
			{
				if (_content_type == "")
				{
					ss >> _content_type;
					if (_content_type[_content_type.size() - 1] == ';')
						_content_type.erase(_content_type.size() - 1);
					ss >> tmp;
					if (tmp.substr(0, 10) == "boundary=")
						_boundary = tmp.substr(10);
				}
				else
					throw(BadRequest);
			}
			else if (tmp == "Accept:")
			{
				if (_accept == "")
					ss >> _accept;
				else
					throw(BadRequest);
			}
			else if (tmp == _boundary)
				break ;
		}
		
		if (_content_length == "")
			throw(LengthRequired);
		
		// todo : not sure
		if (_boundary == "" || _content_type == "" || _accept == "")
			throw(BadRequest);

		// todo : if length too long or type not ok or accept not ok ... ?

		// todo : now read body

	}

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
			if (uri_exist(index_path))
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

	if (uri_exist(path))
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

std::string const &HTTPRequest::get_content_length() const
{
	return _content_length;
}

std::string const &HTTPRequest::get_content_type() const
{
	return _content_type;
}

std::string const &HTTPRequest::get_boundary() const
{
	return _boundary;
}

std::string const &HTTPRequest::get_accept() const
{
	return _accept;
}

std::vector<std::string> const &HTTPRequest::get_content() const
{
	return _content;
}

void	HTTPRequest::print() const
{
	std::cerr	<< "HTTP Request attributes :\n"
				<< "file_uri : " << get_file_uri() <<"\n"
				<< "behavior : " << get_behavior() << "\n"
				<< "method : " << get_method() << "\n"
				<< "HTTP version : " << get_HTTP_versoin() <<"\n"
				<< "Content Length : " << get_content_length() <<"\n"
				<< "Content Type : " << get_content_type() <<"\n"
				<< "Boundary : " << get_boundary() <<"\n"
				<< "Accept : " << get_accept() <<"\n"
				<< "Content : ";
				for (size_t i = 0 ; i < get_content().size() ; ++i)
				{
					std::cerr << i <<" :\n" << get_content()[i] <<"\n";
				}
				std::cerr <<"\n";
}
