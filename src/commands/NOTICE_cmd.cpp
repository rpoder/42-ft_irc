/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE_cmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:29:04 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 14:29:04 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "Server.hpp"

std::string RPL_NOTICE_CHANNEL(User *user, Channel &channel, std::string toSent)
{
	std::string message;

	message = prefix(user) + "NOTICE " + channel.getName() + " " + toSent + SUFFIX;
	return (message);
}

std::string RPL_NOTICE_USER(User *user, User &receiver, std::string toSent)
{
	std::string message;

	message = prefix(user) + "NOTICE " + receiver.getNickname() + " " + toSent + SUFFIX;
	return (message);
}

void	Server::NOTICE_cmd(int client_fd, User *user, std::string args)
{
	(void)		 	client_fd;
	int 			receiver_fd;
	std::string		message;
	Channel			*chan = NULL;
	ChannelMember	*sender;
	User			*receiver = NULL;

	receiver_fd = 0;
	if (splitArgsPRIVMSG(args, &chan, &receiver, message))
	{
		if (chan != NULL)
		{
			sender = chan->findMember(*user);
			if (sender != NULL && sender->isOnline() == true)
				chan->prepSendToAll(RPL_NOTICE_CHANNEL(user, *chan, message), &Server::prepSend, sender);
		}
		else if (receiver != NULL)
		{
			for (std::map<int,User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if (it->second == *receiver)
				{
					receiver_fd = it->first;
					break;
				}
			}
			if (receiver_fd != 0)
				prepSend(receiver_fd, RPL_NOTICE_USER(user, *receiver, message));
		}
	}
}
