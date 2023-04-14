/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:12:00 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/14 17:46:13 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include	<iostream>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<netdb.h>
# include	<arpa/inet.h>
# include	<netinet/in.h>
# include	<stdio.h>
# include	<string.h>
# include	<cstdlib>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<unistd.h>
# include	<sys/epoll.h>
# include	<sstream>
# include	<map>
# include	"User.hpp"
# include	"utils.hpp"

# define	PORT_MIN			1024
# define	PORT_MAX			65535
# define	CONNECTIONS_MAX		20
# define	EPOLL_EVENTS_MAX	1
# define	EPOLL_FD_MAX		21
# define	BUFFER_MAX			2024

typedef addrinfo			t_addrinfo;
typedef sockaddr			t_sockaddr;
typedef sockaddr_storage	t_sockaddr_storage;
typedef epoll_event			t_epoll_event;

class Server
{
	public:
		Server(int port, std::string password);
		Server(const Server &copy);
		~Server();

		Server	&operator=(const Server &copy);
		void	start();
		std::string getPassword();

		class ServerInitException:
			public std::exception
		{
			public:
			virtual const char	*what() const throw();
		};

	private:
		Server();
		void	initSocket();
		void	listen();
		void	handleNewConnection();
		void	handleLostConnection(int fd);
		void	handleInput(int client_fd, char *input);
		void	handleRegistration(int client_fd);
		User	*findUser(int fd);

		void	executeCommand(int client_fd, std::string input);
		void	user_cmd(int client_fd, std::string args);
		void	nick_cmd(int client_fd, std::string args);
		void	pass_cmd(int client_fd, std::string args);
		void	join_cmd(int client_fd, std::string args);

		std::map<int, User>	_users;

		int			_port;
		t_addrinfo	*_serv_info;
		int			_server_fd;
		int			_epoll_fd;
		std::string	_password;

};

#endif