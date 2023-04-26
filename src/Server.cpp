/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:56:34 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 20:45:54 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

Server::Server(int port, std::string password) :
	_message_buffer(this)
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
		throw (Server::ServerException((char *)"Port out of range"));
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	status = getaddrinfo(NULL, str.c_str(), &hints, &_serv_info);
	if (status != 0)
		throw (Server::ServerException());
}

Server::Server(const Server &copy) :
	_message_buffer(this)
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
	_channels = copy._channels;
	_message_to_send = copy._message_to_send;
	_receiver_fd = copy._receiver_fd;
	return(*this);
}

//!-------------------------------ACCESSORS-------------------------------------

std::string Server::getPassword()
{
	return _password;
}

//!-------------------------------FUNCTIONS-------------------------------------

void	Server::prepSend(int fd, std::string message)
{
	t_epoll_event	settings;
	size_t			bytes_sent;

	settings.data.fd = fd;
	settings.events = EPOLLOUT;
	bytes_sent = 0;
	epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &settings);
	_message_buffer.addMessage(fd, message);
}

void	Server::executeCommand(int client_fd, std::string input)
{
	size_t					space_pos;
	std::string				line("");
	std::stringstream		ss(input);
	std::string				commandes[12] = {"NICK", "USER", "PASS", "JOIN", "PING", "PART", "PRIVMSG", "MODE", "KICK", "NOTICE", "LIST", "QUIT"};
	void	(Server::*ptr_f[12])(int client_fd, User *user, std::string args) = {&Server::NICK_cmd, &Server::USER_cmd, &Server::PASS_cmd, &Server::JOIN_cmd, &Server::PING_cmd, &Server::PART_cmd, &Server::PRIVMSG_cmd, &Server::MODE_cmd, &Server::KICK_cmd, &Server::NOTICE_cmd, &Server::LIST_cmd, &Server::QUIT_cmd};
	User					*user;
	std::string				cmd;
	std::string 			args;

	while (std::getline(ss, line))
	{
		user = findUser(client_fd);
		space_pos = line.find(" ");
		if (space_pos == std::string::npos)
		{
			cmd = trimInput(line);
			args = "";
		}
		else
		{
			cmd = line.substr(0, space_pos);
			while (line[space_pos] && line[space_pos] == ' ')
				space_pos++;
			if (space_pos == std::string::npos)
				args = "";
			else
				args = trimInput(line.substr(space_pos));
		}
		for (int i = 0; i < 11; i++)
		{
			if (commandes[i] == cmd && user)
			{
				(this->*(ptr_f[i]))(client_fd, user, args);
				break ;
			}
		}
	}
}

void	Server::handleNewConnection()
{
	t_sockaddr_storage	client_addr;
	int					new_client_fd;
	socklen_t			addr_size;
	t_epoll_event		event_settings;
	User				new_user;

	addr_size = sizeof(client_addr);
	new_client_fd = accept(_server_fd, (struct sockaddr *)&client_addr, &addr_size);
	if (new_client_fd < 0)
		throw(std::exception());
	event_settings.data.fd = new_client_fd;
	event_settings.events = EPOLLIN;
	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, new_client_fd, &event_settings);
	_users[new_client_fd] = new_user;
}

void	Server::handleLostConnection(int fd)
{
	User	*user;

	user = findUser(fd);
	if (user)
		QUIT_cmd(fd, user, "");
}

void	Server::handleInput(int client_fd, char *input)
{
	static std::string	input_str;
	size_t				end_of_line;

	input_str += static_cast<std::string>(input);
	end_of_line = input_str.find("\n");
	if (end_of_line != input_str.npos)
	{
		displayMessage("magenta", input_str);
		executeCommand(client_fd, input_str);
		input_str.clear();
	}
}

void	Server::handleRegistration(int client_fd)
{
	User		*user;
	std::string	message;

	user = findUser(client_fd);
	if (user && user->getIsRegistered() == false
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

		message = prefix(user) + "001 " + user->getNickname()
		+ " :Welcome chez les petits poux " + user->getNickname()
		+ "!" + user->getUsername() + "@localhost" + SUFFIX;
		prepSend(client_fd, message);
	}
}

void	Server::handleSend(int fd, std::string message)
{
	size_t bytes_sent;

	bytes_sent = 0;
	do
	{
		message = message.substr(bytes_sent, message.length() - bytes_sent);
		bytes_sent = send(fd, message.c_str(), message.length(), 0);
		if (bytes_sent == static_cast<size_t>(-1))
		{
			displayMessage("red", "Err:	error while sending message");
			break;
		}
	} while (bytes_sent != 0);
}

User	*Server::findUser(int fd)
{
	std::map<int,User>::iterator	it;

	it = _users.find(fd);
	if (it == _users.end())
		return (NULL);
	return (&(it->second));
}

BotGame	*Server::findGame(int fd)
{
	std::map<int, BotGame>::iterator	it;

	it = _games.find(fd);
	if (it == _games.end())
	{
		return (NULL);
	}
	return (&(it->second));
}

User	*Server::findUser(std::string nickname)
{
	for (std::map<int,User>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second.getNickname() == nickname)
			return (&(it->second));
	}
	return (NULL);
}

Channel	*Server::findChannel(std::string &name)
{
	std::map<std::string, Channel>::iterator	it;

	it = _channels.find(name);
	if (it == _channels.end())
		return (NULL);
	return (&(it->second));
}

void	Server::listen()
{
	std::stringstream	ss;
	std::string			port;

	t_epoll_event		event_settings;

	if (::listen(_server_fd, CONNECTIONS_MAX) != 0)
		throw (Server::ServerException());

	_epoll_fd = epoll_create(EPOLL_FD_MAX);
	if (_epoll_fd == -1)
		throw (Server::ServerException());
	event_settings.data.fd = _server_fd;
	event_settings.events = EPOLLIN;
	ss << _port;
	port = ss.str();
	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _server_fd, &event_settings);
	displayMessage("blue", "Server started: listening on port " + port);
}

void	Server::waitEvents()
{
	t_epoll_event		events[EPOLL_EVENTS_MAX];
	int					event_count;
	char				input[BUFFER_MAX];


	event_count = epoll_wait(_epoll_fd, events, EPOLL_EVENTS_MAX, -1);
	if (event_count == -1)
		throw (Server::ServerException());
	for (int i = 0; i < event_count; i++)
	{
		if (events[i].data.fd == _server_fd)
			handleNewConnection();
		else if (events[i].events & EPOLLIN)
		{
			memset(input, 0, BUFFER_MAX);
			if (recv(events[i].data.fd, input, BUFFER_MAX, 0) == 0)
				handleLostConnection(events[i].data.fd);
			else
				handleInput(events[i].data.fd, input);
		}
		else if (events[i].events & EPOLLOUT)
			_message_buffer.sendTo(events[i].data.fd, &Server::handleSend);
		handleRegistration(events[i].data.fd);
	}
}

void	Server::initSocket()
{
	int	setsock_opt;

	_server_fd = socket(_serv_info->ai_family, _serv_info->ai_socktype, _serv_info->ai_protocol);
	if (_server_fd == -1)
		throw (Server::ServerException());
	setsock_opt = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &setsock_opt, sizeof(setsock_opt)) == -1)
		throw (Server::ServerException());
	if (bind(_server_fd, _serv_info->ai_addr, _serv_info->ai_addrlen) != 0)
		throw (Server::ServerException());
}

void	Server::start()
{
	initSocket();
	listen();
}

//!-----------------------------MEMBER CLASSES----------------------------------

Server::ServerException::ServerException():
	_message(strerror(errno))
{}

Server::ServerException::ServerException(char *message):
	_message(message)
{}

Server::ServerException::~ServerException() throw()
{}

const char	*Server::ServerException::what() const throw()
{
	return(_message);
}
