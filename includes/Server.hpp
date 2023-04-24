/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:12:00 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/24 14:03:27 by rpoder           ###   ########.fr       */
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
# include	<cerrno>
# include	<sys/epoll.h>
# include	<sstream>
# include	<cstring>
# include	<map>
# include	<algorithm>
# include	"User.hpp"
# include	"utils.hpp"
# include	"errors.hpp"
# include	"Channel.hpp"
# include	"replies.hpp"


# define	PORT_MIN			1024
# define	PORT_MAX			65535
# define	CONNECTIONS_MAX		20
# define	EPOLL_EVENTS_MAX	1
# define	EPOLL_FD_MAX		21
# define	BUFFER_MAX			2024
# define	SUFFIX				"\r\n"

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
				ServerInitException();
				ServerInitException(char *message);
				virtual const char	*what() const throw();
				virtual				~ServerInitException() throw();

			private:
				char	*_message;
		};

		void	sendMessage(int client_fd, std::string message);

	private:
		Server();
		void	initSocket();
		void	listen();
		void	handleNewConnection();
		void	handleLostConnection(int fd);
		void	handleInput(int client_fd, char *input);
		void	handleRegistration(int client_fd);
		void	handleSend(int client_fd);

		User	*findUser(int fd);
		Channel	*findChannel(std::string &name);

		void	executeCommand(int client_fd, std::string input);
		void	USER_cmd(int client_fd, User *user, std::string args);
		void	NICK_cmd(int client_fd, User *user, std::string args);
		void	PASS_cmd(int client_fd, User *user, std::string args);
		void	JOIN_cmd(int client_fd, User *user, std::string args);
		void	PING_cmd(int client_fd, User *user, std::string args);
		void	PART_cmd(int client_fd, User *user, std::string args);
		void	MODE_cmd(int client_fd, User *user, std::string args);

		void	sendJoinRPL(int client_fd, ChannelMember &member, Channel &channel);

		std::map<int, User>				_users;
		std::map<std::string, Channel>	_channels;

		int								_port;
		t_addrinfo						*_serv_info;
		int								_server_fd;
		int								_epoll_fd;
		std::string						_password;

		int								_receiver_fd;
		std::string						_message_to_send;
};

#endif
