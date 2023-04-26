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

void	Server::NOTICE_cmd(int client_fd, User *user, std::string args)
{
	(void)		 	client_fd;
	
	int 			receiver_fd;
	std::string		destinataire;
	std::string		message;
	Channel			*chan;
	ChannelMember	*sender;
	User			*receiver;

	receiver_fd = 0;
	destinataire = splitArgsPRIVMSG(args, message);
	chan = findChannel(destinataire);
	receiver = findUser(destinataire);
	if (!destinataire.empty())
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
