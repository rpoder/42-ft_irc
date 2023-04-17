/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:56:34 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 14:06:41 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

Server::Server(int port, std::string password)
{
	t_addrinfo			hints;
	int					status;
	std::stringstream	ss;
	std::string			str;

	ss << port;
	ss >> str;
	_port = port;
	_server_fd = 0;
	_password = password;

	if (_port < PORT_MIN || _port > PORT_MAX)
		throw (Server::ServerInitException((char *)"Port out of range"));
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
	_port = copy._port;
	_serv_info = copy._serv_info;
	_server_fd = copy._server_fd;
	_epoll_fd = copy._epoll_fd;
	_password = copy._password;
	_users = copy._users;
	return(*this);
}

//!-------------------------------ACCESSORS-------------------------------------

std::string Server::getPassword()
{
	return _password;
}

//!-------------------------------FUNCTIONS-------------------------------------

void	Server::handleSend(int client_fd, std::string message)
{
	t_epoll_event	settings;
	size_t			bytes_sent;

	settings.data.fd = client_fd;
	settings.events = EPOLLOUT;
	bytes_sent = 0;
	//TODO check error
	epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, client_fd, &settings);
	do
	{
		message = message.substr(bytes_sent, message.length() - bytes_sent);
		bytes_sent = send(client_fd, message.c_str(), message.length(), 0);
	} while (bytes_sent != 0);

	settings.events = EPOLLIN;
	epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, client_fd, &settings);
	//TODO gerer cas d'erreur de send
}

void	Server::executeCommand(int client_fd, std::string input)
{
	size_t						separator_pos;
	std::string				line("");
	std::stringstream		ss(input);
	std::string				commandes[5] = {"NICK", "USER", "PASS", "JOIN", "PING"};
	void	(Server::*ptr_f[5])(int client_fd, User *user, std::string args) = {&Server::NICK_cmd, &Server::USER_cmd, &Server::PASS_cmd, &Server::JOIN_cmd, &Server::PING_cmd};
	User					*user;

	while (std::getline(ss, line))
	{
		user = findUser(client_fd);
		separator_pos = line.find(" ");
		for (int i = 0; i < 5; i++)
		{
			if (commandes[i] == line.substr(0, separator_pos) && user) {
				std::string args;
				if (separator_pos == std::string::npos)
					args = "";
				else
					args = line.substr(separator_pos);
				(this->*(ptr_f[i]))(client_fd, user, trimArgs(args));
				break ;
			}
		}
	}
}

// create a socket, clean the socket memory, link socket to a port
void	Server::initSocket()
{
	int	setsock_opt;

	_server_fd = socket(_serv_info->ai_family, _serv_info->ai_socktype, _serv_info->ai_protocol);
	if (_server_fd == -1)
		throw (Server::ServerInitException());
	setsock_opt = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &setsock_opt, sizeof(setsock_opt)) == -1)
		throw (Server::ServerInitException());
	if (bind(_server_fd, _serv_info->ai_addr, _serv_info->ai_addrlen) != 0)
		throw (Server::ServerInitException());
}

void	Server::handleNewConnection()
{
	displayMessage("orange", "[handleNewConnection called]");
	t_sockaddr_storage	client_addr;
	int					new_client_fd;
	socklen_t			addr_size;
	t_epoll_event		event_settings;
	User				new_user;

	addr_size = sizeof(client_addr);
	new_client_fd = accept(_server_fd, (struct sockaddr *)&client_addr, &addr_size);
	if (new_client_fd < 0)
	{
		perror("accept");
		throw(std::exception());
	}
	std::cout << "New client on fd " << new_client_fd << std::endl;
	event_settings.data.fd = new_client_fd;
	// event_settings.events = EPOLLIN | EPOLLOUT;
	event_settings.events = EPOLLIN;
	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, new_client_fd, &event_settings);

	// create new empty user on map<fd, User>
	new_user.setFd(new_client_fd);
	_users[new_client_fd] = new_user;
}

void	Server::handleLostConnection(int fd)
{
	displayMessage("orange", "[handleLostConnection called]");

	_users.erase(fd);
	displayMessage("red", "Connection closed");
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
	close(fd);
}

void	Server::handleInput(int client_fd, char *input)
{
	char *dup;

	dup = strdup(input);
	std::string	input_str(dup);
	std::string str;

	std::cout << "input: " << input_str ;
	executeCommand(client_fd, input_str);
}

void	Server::handleRegistration(int client_fd)
{
	displayMessage("orange", "[handleRegistration called]");
	User		*user;
	std::string	message;

	user = findUser(client_fd);
	if (!user)
		std::cout << "on handle registration user doesnt exist" << std::endl;
	else if (user && user->getIsRegistered() == false
		&& user->getNickname().length() > 0
		&& user->getUsername().length() > 0)
	{
		if (user->getPassword() != _password)
		{
			displayMessage("red", "Wrong password entered");
			handleLostConnection(client_fd);
			return ;
		}
		user->setIsRegistered(true);
		printUser(client_fd, *user);

		message = prefix(*user) + "001 " + user->getNickname()
		+ " :Welcome chez les petits poux " + user->getNickname()
		+ "!" + user->getUsername() + "@localhost" + SUFFIX;
		handleSend(client_fd, message);
	}
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
	char				input[BUFFER_MAX];
	t_epoll_event		event_settings;

	// listen
	if (::listen(_server_fd, CONNECTIONS_MAX) != 0)
		throw (Server::ServerInitException());

	_epoll_fd = epoll_create(EPOLL_FD_MAX);
	if (_epoll_fd == -1)
	{
		// perror("epoll");
		throw (Server::ServerInitException());
	}

	event_settings.data.fd = _server_fd;
	event_settings.events = EPOLLIN;
	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _server_fd, &event_settings);
	std::cout << std::endl << "\033[1;37mServer started: listening on port " << _port << "\033[0m" << std::endl;
	while (1)
	{
		event_count = epoll_wait(_epoll_fd, events, EPOLL_EVENTS_MAX, -1);
		if (event_count == -1)
			throw (Server::ServerInitException());
		for (int i = 0; i < event_count; i++)
		{
			// std::cout << "fd" << events[i].data.fd << std::endl;
			if (events[i].data.fd == _server_fd)
			{
				handleNewConnection();
			}
			else if (events[i].events & EPOLLIN)
			{
				memset(input, 0, BUFFER_MAX);
				if (recv(events[i].data.fd, input, BUFFER_MAX, 0) == 0)
					handleLostConnection(events[i].data.fd);
				else
				{
					// try
					// {
						handleInput(events[i].data.fd, input);
					// }
					// catch (std::exception &err)
					// {
					// 	// break ;
					// }

				}
			}
			handleRegistration(events[i].data.fd);
		}
		// std::cout << "boucle inf" << std::endl;
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

Server::ServerInitException::ServerInitException():
	_message(strerror(errno))
{}

Server::ServerInitException::ServerInitException(char *message):
	_message(message)
{}

Server::ServerInitException::~ServerInitException() throw()
{}

const char	*Server::ServerInitException::what() const throw()
{
	return(_message);
}
