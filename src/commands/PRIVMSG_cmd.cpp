/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG_cmd.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:29:41 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 14:29:41 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::PRIVMSG_cmd(int client_fd, User *user, std::string args)
{
	std::string		destinataire;
	std::string		message;
	Channel			*chan;
	ChannelMember	*sender;
	User			*receiver;
	int				receiver_fd;

	receiver_fd = 0;
	destinataire = splitArgsPRIVMSG(args, message);
	chan = findChannel(destinataire);
	receiver = findUser(destinataire);
	if (destinataire.empty())
		prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "PRIVMSG", ":Not enough parameters"));
	else
	{
		if (destinataire[0] == '#' && chan == NULL)
			prepSend(client_fd, buildErrorMessage(ERR_CANNOTSENDTOCHAN, user, "PRIVMSG", destinataire));
		else if (destinataire[0] == '#')
		{
			sender = chan->findMember(*user);
			if (sender == NULL || (sender != NULL && sender->isOnline() == false))
				prepSend(client_fd, buildErrorMessage(ERR_CANNOTSENDTOCHAN, user, "PRIVMSG", destinataire));
			else
				chan->prepSendToAll(RPL_PRIVMSG_CHANNEL(user, *chan, message), &Server::prepSend, sender);
		}
		// else if (destinataire == "bot")
		// {

		// }
		else if (receiver == NULL)
			prepSend(client_fd, buildErrorMessage(ERR_NOSUCHNICK, user, "PRIVMSG", destinataire));
		else
		{
			for (std::map<int,User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if (it->second == *receiver)
				{
					receiver_fd = it->first;
					break;
				}
			}
			if (receiver_fd == 0)
				prepSend(client_fd, buildErrorMessage(ERR_NOSUCHNICK, user, "PRIVMSG", args.substr(0, args.find(' '))));
			else
				prepSend(receiver_fd, RPL_PRIVMSG_USER(user, *receiver, message));
		}
	}
}
