#pragma once
#include "webserv.hpp"

/*
Conf File
*/

class InvalidConfFilePath : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Invalid Configuration File Path";
		}
};

class ConfFileParseError : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Configuration File Parse Error";
		}
};

/*
Socket
*/

class FailToCreateSocket : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Fail To Create Socket";
		}
};

class FailToSetSocketOption : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Fail To Set Socket Option";
		}
};

class FailToBind : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Fail To Bind";
		}
};

class FailToListen : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Fail To Listen";
		}
};

/*
Connection
*/

class FailToCreateEpoll : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Fail To Create Epoll";
		}
};

class FailToControlEpoll : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Fail To Control Epoll";
		}
};

/*
HTTP
*/

