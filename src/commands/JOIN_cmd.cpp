/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/18 14:08:40 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::JOIN_cmd(int client_fd, User *user, std::string args)
{
	std::map<std::string, Channel>::iterator it;
	std::string name(args);

	displayMessage("orange", "[JOIN_cmd function called]");

	if (name[0] != '#')
		handleSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "JOIN", ""));
	else
	{
		it = _channels.find(name);
		// Si le channel n'existe pas, le channel doit etre cree, le membre doit etre cree
		if (it == _channels.end())
		{
			Channel 		newChannel(name);
			ChannelMember	newChannelMember(user, true, client_fd);
			
			newChannel.addMember(newChannelMember);
			_channels[name] = newChannel;
			sendJoinRPL(client_fd, newChannelMember, newChannel);

		}
		else if (it != _channels.end() && it->second.findMember(*user) == NULL) // Si le channel existe mais que le user n'a jamais join le channel
		{
			ChannelMember	newChannelMember(user, false, client_fd);

			it->second.addMember(newChannelMember);
			sendJoinRPL(client_fd, newChannelMember, it->second);
			
		}
		else // le channel existe, mais le user est deja membre
		{
			ChannelMember	*member;

			member = it->second.findMember(*user);
			member->setIsOnline(true);
			sendJoinRPL(client_fd, *member, it->second);
		}
	}
}

void	Server::sendJoinRPL(int client_fd, ChannelMember &member, Channel &channel)
{
	
	handleSend(client_fd, RPL_NAMREPLY(member, channel));
	handleSend(client_fd, RPL_ENDOFNAMES(member, channel));
	//SEND TO ALL
	for (std::vector<ChannelMember>::iterator it = channel._members.begin(); it != channel._members.end(); it++)
		handleSend((*it).getFd(), RPL_JOIN(member, channel));
}