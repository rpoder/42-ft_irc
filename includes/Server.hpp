/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:12:00 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/09 20:31:47 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include	<iostream>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<netdb.h>
#include	<arpa/inet.h>
# include	<netinet/in.h>
# include	<stdio.h>
# include	<string.h>
# include	<cstdlib>
# include	<sys/types.h>
# include	<sys/socket.h>


# define	PORT_MIN		1024
# define	PORT_MAX		65535
# define	CONNECTIONS_MAX	20

typedef addrinfo t_addrinfo;
typedef sockaddr t_sockaddr;

class Server
{
	public:
		Server();
		Server(const Server &copy);
		~Server();

		Server	&operator=(const Server &copy);
		void	listen(unsigned int port);

	private:
		int			_status;
		t_addrinfo	_hints;
		t_addrinfo	*_serv_info;
		int			_socket_fd;

		class ServerInitException:
			std::exception
		{
			const char	*what() const throw();
		};
};

#endif
