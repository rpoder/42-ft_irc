/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:52:17 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 18:13:45 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::QUIT_cmd(int fd, User *user, std::string args)
{
	(void) args;

	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		Channel &channel = it->second;
		for (std::vector<ChannelMember>::iterator it = channel._members.begin(); it != channel._members.end(); it++)
		{
			if (*(it->getUser()) == *user)
			{
				channel._members.erase(it);
				channel._members.front().setIsOperator(true);
				break ;
			}
		}
	}
	_users.erase(fd);
	displayMessage("red", "Connection closed");
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
	close(fd);
}
