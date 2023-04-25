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

bool    Server::splitArgsPRIVMSG(std::string args, Channel **channel, User **receveur, std::string &message)
{
    size_t i;
    std::string destinataire;

    i = 0;
    while (args[i] && args[i] != ' ')
        i++;
    destinataire = args.substr(0, i);
    if (destinataire[0] == '#')
        *channel = findChannel(destinataire);
    else
        *receveur = findUser(destinataire);
    if (args[i] == ' ')
        i++;
    std::cout << "splitArgs1" << std::endl;
    if (i == args.length() || (args[i] && args[i] != ':'))
        return false;
    message = args.substr(i);
    std::cout << "splitArgs2" << std::endl;
    return true;
}

std::string RPL_PRIVMSG_CHANNEL(User *user, Channel &channel, std::string toSent)
{
	std::string message;

	message = prefix(user) + "PRIVMSG " + channel.getName() + " " + toSent + SUFFIX;
	return (message);
}

std::string RPL_PRIVMSG_USER(User *user, User &receveur, std::string toSent)
{
	std::string message;

	message = prefix(user) + "PRIVMSG " + receveur.getNickname() + " " + toSent + SUFFIX;
	return (message);
}

void    Server::PRIVMSG_cmd(int client_fd, User *user, std::string args)
{
    (void) client_fd;
    (void) user;
    (void) args;

    std::string message;
    Channel *chan = NULL;
    ChannelMember *sender;
    User *receveur = NULL;
    int receveur_fd;

    displayMessage("orange", "[PRIVMSG_cmd function called]");

    receveur_fd = 0;
    if (!splitArgsPRIVMSG(args, &chan, &receveur, message))
        prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "PRIVMSG", ":Not enough parameters"));
    else
    {
        if (args[0] == '#' && chan == NULL)
            prepSend(client_fd, buildErrorMessage(ERR_CANNOTSENDTOCHAN, user, "PRIVMSG", args.substr(0, args.find(' '))));
        else if (args[0] == '#')
        {
            sender = chan->findMember(*user);
            if (sender == NULL || (sender != NULL && sender->isOnline() == false))
                prepSend(client_fd, buildErrorMessage(ERR_CANNOTSENDTOCHAN, user, "PRIVMSG", args.substr(0, args.find(' '))));
            else
                chan->prepSendToAll(RPL_PRIVMSG_CHANNEL(user, *chan, message), &Server::prepSend, sender);
        }
        else if (receveur == NULL)
            prepSend(client_fd, buildErrorMessage(ERR_NOSUCHNICK, user, "PRIVMSG", args.substr(0, args.find(' '))));
        else
        {
            for (std::map<int,User>::iterator it = _users.begin(); it != _users.end(); it++)
            {
                if (it->second == *receveur)
                {
                    receveur_fd = it->first;
                    break;
                }
            }
	        if (receveur_fd == 0)
                prepSend(client_fd, buildErrorMessage(ERR_NOSUCHNICK, user, "PRIVMSG", args.substr(0, args.find(' '))));
            else
                prepSend(receveur_fd, RPL_PRIVMSG_USER(user, *receveur, message));
        }
    }
}