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
	(void)				port;
	t_addrinfo			hints;
	int					status;
	std::stringstream	ss;
	std::string			 str;

	ss << port;
	ss >> str;
	_port = port;
	_server_fd = 0;
	//TODO check if port is in range (defines are in the header)
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	status = getaddrinfo("localhost", str.c_str(), &hints, &_serv_info);
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
	if (_server_fd >= 0)
		close(_server_fd);
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
	_server_fd = socket(_serv_info->ai_family, _serv_info->ai_socktype, _serv_info->ai_protocol);
	if (_server_fd == -1)
		throw (Server::ServerInitException());
		//? ERRNO is available for this ret
		//? maybe check return errno in a arg_exception
	setsock_opt = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &setsock_opt, sizeof(setsock_opt)) == -1)
	{
		//TODO throw exception instead
		perror("setsockopt");
		exit(1);
	}
	if (bind(_server_fd, _serv_info->ai_addr, _serv_info->ai_addrlen) != 0)
	{
		perror("bind");
		throw (Server::ServerInitException());
	}
}

void	Server::handleNewConnection()
{
	t_sockaddr_storage	client_addr;
	int					new_client_fd;
	socklen_t			addr_size;
	t_epoll_event		event_settings;

	event_settings.data.fd = _server_fd;
	event_settings.events = EPOLLIN; //flag d'ecoute en read
	std::cout << "New connection on server." << std::endl;
	addr_size = sizeof(client_addr);
	new_client_fd = accept(_server_fd, (struct sockaddr *)&client_addr, &addr_size);
	if (new_client_fd < 0)
	{
		perror("accept");
		throw(std::exception());
	}
	std::cout << "New client on fd " << new_client_fd << std::endl;
	event_settings.data.fd = new_client_fd;
	event_settings.events = EPOLLIN | EPOLLET;
	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, new_client_fd, &event_settings);


	// char message[BUFFER_MAX];
	// memset(message, 0, BUFFER_MAX);
	// recv(new_client_fd, message, BUFFER_MAX, 0);
	// handleInput(message);
}

void	Server::handleLostConnection(int fd)
{
	_users.erase(fd);
	std::cout << "Client closed\n" << std::endl;
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
}

void	Server::handleInput(int sender_fd, char *message)
{
	User new_user;
	std::string nickname;

	nickname = message;

	if (strncmp(message, "USER", 4) == 0)
	{
		new_user.setNickName(nickname.substr(5));
		_users[sender_fd] = new_user;
		::printContainer(_users);
	}
	std::cout << "New message---------------------" << std::endl;
	std::cout << "|" << message << "|" << std::endl;
	// send(events[i].data.fd, "coucou\n", 7, 0);
}

User	*Server::findUser(int fd)
{
	std::map<int,User>::iterator	it;

	it = _users.find(fd);
	if (it == _users.end())
		return (NULL);
	return (&(it->second));
}

// start listening on socket
void	Server::listen()
{
	t_epoll_event		events[EPOLL_EVENTS_MAX];
	int					event_count;
	char				message[BUFFER_MAX];
	t_epoll_event		event_settings;



	// listen
	if (::listen(_server_fd, CONNECTIONS_MAX) != 0)
		throw (Server::ServerInitException());

	_epoll_fd = epoll_create(EPOLL_FD_MAX);
	if (_epoll_fd == -1)
	{
		perror("epoll");
		throw (Server::ServerInitException());
	}

	event_settings.data.fd = _server_fd;
	event_settings.events = EPOLLIN; //flag d'ecoute en read
	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _server_fd, &event_settings);
	std::cout << "Server started: listening on port " << _port << std::endl;
	// accept

	while (1)
	{
		std::cout << "before wait" << std::endl;
		event_count = epoll_wait(_epoll_fd, events, EPOLL_EVENTS_MAX, -1);
		if (event_count == -1)
		{
			perror("epoll_wait");
			break ;
		}
		std::cout << "after wait" << std::endl;
		for (int i = 0; i < event_count; i++)
		{
			User *tmp;

			tmp = findUser(events[i].data.fd);
			if (tmp)
				std::cout << tmp->getNickName() << std::endl;
			if (events[i].data.fd == _server_fd)
			{
				handleNewConnection();
			}
			else if (events[i].events & EPOLLIN)
			{
				memset(message, 0, BUFFER_MAX);
				if (recv(events[i].data.fd, message, BUFFER_MAX, 0) == 0)
					handleLostConnection(events[i].data.fd);
				else
					handleInput(events[i].data.fd, message);
			}
		}
		memset(events, 0, sizeof(events));
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
