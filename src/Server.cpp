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

Server::Server(int port, std::string password)
{
	t_addrinfo			hints;
	int					status;
	std::stringstream	ss;
	std::string			 str;

	ss << port;
	ss >> str;
	_port = port;
	_server_fd = 0;
	_password = password;

	//TODO check if port is in range (defines are in the header)
	if (_port < PORT_MIN || _port > PORT_MAX)
		throw (Server::ServerInitException());
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

std::string Server::getPassword()
{
    return _password;
}

//!-------------------------------FUNCTIONS-------------------------------------

void	Server::executeCommand(int client_fd, std::string input)
{
	int						separator_pos;
	std::string				line("");
	std::stringstream		ss(input);
	std::string				commandes[4] = {"NICK", "USER", "PASS", "JOIN"};
	void	(Server::*ptr_f[4])(int client_fd, std::string args) = {&Server::nick_cmd, &Server::user_cmd, &Server::pass_cmd, &Server::join_cmd};

	while (std::getline(ss, line))
	{
		separator_pos = line.find(" ");
		for (int i = 0; i < 4; i++)
        {
            if (commandes[i] == line.substr(0, separator_pos)) {
				// std::cout << "line: " << line << std::endl;
				std::string args(line.substr(separator_pos + 1));
                (this->*(ptr_f[i]))(client_fd, trimArgs(args));
			}
        }
	}
}

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
	User				new_user;

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

	// create new empty user on map<fd, User>
	_users[new_client_fd] = new_user;
}

void	Server::handleLostConnection(int fd)
{
	User *user;

	user = findUser(fd);

	user->setIsRegistered(false);
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
	User		*user;
	std::string	str;

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
		size_t	i;

		i = user->getUsername().find(" ");
		if (i != std::string::npos)
		{
			str = ":" + user->getNickname()
			+ "!" + user->getUsername().substr(0, i) + "@localhost 001 " + user->getNickname()
			+ " :Welcome to the Internet Relay Network " + user->getNickname()
			+ "!" + user->getUsername().substr(0, i) + "@localhost\r\n";
		}
		send(client_fd, (char *)str.c_str(), str.length(), 0);
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
		perror("epoll");
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
		{
			perror("epoll_wait");
			break ;
		}
		for (int i = 0; i < event_count; i++)
		{
			// std::cout << events[i].data.fd << std::endl;
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
					handleInput(events[i].data.fd, input);
			}
			handleRegistration(events[i].data.fd);
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
	return("Error occurred while initialiazing server.");
};