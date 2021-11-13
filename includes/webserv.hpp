#pragma once

// C library

#include <arpa/inet.h> // htons, htonl, ntohs, ntohl, inet_addr
#include <sys/select.h> // select
#include <poll.h> // poll
#include <sys/socket.h> // socket, accept, listen, send, recv, bind, connect, setsockopt, getsockname
#include <fcntl.h> // fcntl


#ifdef __linux__
	#include <sys/epoll.h> // epoll
#else
	#include <sys/event.h> // kqueue
#endif

// C++ library

#include <iostream>
