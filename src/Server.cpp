/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   Server.cpp										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rpoder <rpoder@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/09 19:11:40 by rpoder			#+#	#+#			 */
/*   Updated: 2023/04/09 19:43:20 by rpoder		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "Server.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

Server::Server(int port)
{
	(void) port;
	t_addrinfo	hints;
	int			status;

	_socket_fd = 0;
	//TODO check if port is in range (defines are in the header)
	memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	hints.ai_flags = AI_PASSIVE; // fill in my IP for me
	status = getaddrinfo("localhost", "3493", &hints, &_serv_info);
	if (status != 0)
		throw (Server::ServerInitException());
}

Server::Server(const Server &copy)
{
	*this = copy;
}

//!-------------------------------DESTRUCTOR------------------------------------

Server::~Server()
{
	if (_socket_fd >= 0)
		close(_socket_fd);
	freeaddrinfo(_serv_info);
}

//!-------------------------------OPERATOR--------------------------------------

Server	&Server::operator=(const Server &copy)
{
	//TODO complete this part
	(void) copy;
	return(*this);
}

//!-------------------------------ACCESSORS-------------------------------------

//!-------------------------------FUNCTIONS-------------------------------------

// create a socket, clean the socket memory, link socket to a port
void	Server::initSocket()
{
	int	setsock_opt;

	// socket
	_socket_fd = socket(_serv_info->ai_family, _serv_info->ai_socktype, _serv_info->ai_protocol);
	if (_socket_fd == -1)
		throw (Server::ServerInitException());
		//? ERRNO is available for this ret
		//? maybe check return errno in a arg_exception
	setsock_opt = 1;
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &setsock_opt, sizeof(setsock_opt)) == -1)
	{
		//TODO throw exception instead
		perror("setsockopt");
		exit(1);
	}
	if (bind(_socket_fd, _serv_info->ai_addr, _serv_info->ai_addrlen) != 0)
	{
		perror("bind");
		throw (Server::ServerInitException());
	}
}

// start listening on socket
void	Server::listen()
{
	t_sockaddr_storage	client_addr;
	int					new_fd;
	socklen_t			addr_size;
	int					epoll_fd;
	t_epoll_event		event;
	t_epoll_event		events[EPOLL_EVENTS_MAX];
	int					event_count;

	// listen
	if (::listen(_socket_fd, CONNECTIONS_MAX) != 0)
		throw (Server::ServerInitException());

	epoll_fd = epoll_create(EPOLL_FD_MAX);
	if (epoll_fd == -1)
	{
		perror("epoll");
		throw (Server::ServerInitException());
	}
	event.data.fd = _socket_fd;
	event.events = EPOLLIN;
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, _socket_fd, &event);
	std::cout << _socket_fd << std::endl;
	// accept
	while (1)
	{
		event_count = epoll_wait(epoll_fd, events, EPOLL_EVENTS_MAX, -1);
		for (int i = 0; i < event_count; i++)
		{
			if (events[i].data.fd == _socket_fd)
			{
				addr_size = sizeof(client_addr);
				new_fd = accept(_socket_fd, (struct sockaddr *)&client_addr, &addr_size);
				if (new_fd < 0)
				{
					perror("accept");
					break ;
				}
			}
			// bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
			// printf("%zd bytes read.\n", bytes_read);
			// read_buffer[bytes_read] = '\0';
			// printf("Read '%s'\n", read_buffer);

			// if(!strncmp(read_buffer, "stop\n", 5))
			// running = 0;
		}
		if (event_count == -1)
		{
			perror("epoll_wait");
			break ;
		}
		// std::cerr << event_count << std::endl;

	}
}

void	Server::start()
{
	// TODO try and catch
	initSocket();
	listen();
}

//!-----------------------------MEMBER CLASSES----------------------------------

const char	*Server::ServerInitException::what() const throw()
{
	return ("could't instantiate the server");
}
