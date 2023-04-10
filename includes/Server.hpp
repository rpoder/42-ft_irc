/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:12:00 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/10 17:55:53 by rpoder           ###   ########.fr       */
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

# define	PORT_MIN			1024
# define	PORT_MAX			65535
# define	CONNECTIONS_MAX		20
# define	EPOLL_EVENTS_MAX	1
# define	EPOLL_FD_MAX		20

typedef addrinfo			t_addrinfo;
typedef sockaddr			t_sockaddr;
typedef sockaddr_storage	t_sockaddr_storage;
typedef epoll_event			t_epoll_event;

class Server
{
	public:
		Server(int port);
		Server(const Server &copy);
		~Server();

		Server	&operator=(const Server &copy);
		void	start();

	private:
		Server();
		void	initSocket();
		void	listen();

		t_addrinfo	*_serv_info;
		int			_socket_fd;

		class ServerInitException:
			std::exception
		{
			const char	*what() const throw();
		};
};

#endif
