/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:59:53 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/24 15:21:19 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

// # include "Server.hpp"
# include "User.hpp"
# include <utility>
# include	<iostream>
# include	<sys/types.h>
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
# include	<vector>
# include	<algorithm>

class Server;

class Message
{
	public:
		Message(Server *server);
		Message(const Message &copy);
		~Message();

		void	addMessage(int fd, std::string message);
		void	sendTo(int fd, void (Server::*sendMethod)(int, std::string));

		Message	&operator=(const Message &copy);

	private:
		Message();
		std::vector< std::pair<int, std::string> > _messages;
		Server										*_server_instance;
};

#endif
