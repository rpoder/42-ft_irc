/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG_cmd.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:42:37 by caubry            #+#    #+#             */
/*   Updated: 2023/04/25 13:42:37 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string RPL_NOTICE_CHANNEL(User *user, Channel &channel, std::string toSent)
{
	std::string message;

	message = prefix(user) + "NOTICE " + channel.getName() + " " + toSent + SUFFIX;
	return (message);
}

std::string RPL_NOTICE_USER(User *user, User &receveur, std::string toSent)
{
	std::string message;

	message = prefix(user) + "NOTICE " + receveur.getNickname() + " " + toSent + SUFFIX;
	return (message);
}

void    Server::NOTICE_cmd(int client_fd, User *user, std::string args)
{
    (void) client_fd;
    (void) user;
    (void) args;

    std::string message;
    Channel *chan = NULL;
    ChannelMember *sender;
    User *receveur = NULL;
    int receveur_fd;

    displayMessage("orange", "[NOTICE_cmd function called]");

    receveur_fd = 0;
    if (splitArgsPRIVMSG(args, &chan, &receveur, message))
    {
        std::cout << "condition notice cmd remplie" << std::endl;
        if (chan != NULL)
        {
            sender = chan->findMember(*user);
            if (sender != NULL && sender->isOnline() == true)
                chan->prepSendToAll(RPL_NOTICE_CHANNEL(user, *chan, message), &Server::prepSend, sender);
        }
        else if (receveur != NULL)
        {
            std::cout << "avant boucle map" << std::endl;
            for (std::map<int,User>::iterator it = _users.begin(); it != _users.end(); it++)
            {
                std::cout << "boucle map" << std::endl;
                if (it->second == *receveur)
                {
                    receveur_fd = it->first;
                    break;
                }
            }
            std::cout << "apres boucle map" << std::endl;
	        if (receveur_fd != 0)
                prepSend(receveur_fd, RPL_NOTICE_USER(user, *receveur, message));
        }
    }
}