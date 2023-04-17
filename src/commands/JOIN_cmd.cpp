/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 18:46:20 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::JOIN_cmd(int client_fd, User *user, std::string args)
{
	(void) client_fd;
	std::string str;
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
			handleSend(client_fd, RPL_NAMREPLY(newChannelMember, newChannel));
			// std::cout << "Membres new channel " << newChannel.listMembers() << std::endl;
		}
		else if (it != _channels.end() && it->second.findMember(*user) == NULL) // Si le channel existe mais aque le user n'a jamais join le channel
		{
			ChannelMember	newChannelMember(user, false, client_fd);
			
			it->second.addMember(newChannelMember);
		}
		else // le channel existe, mais le user est deja membre
		{
			ChannelMember	*member;

			member = it->second.findMember(*user);

			member->setIsOnline(true);
		}













		
			// it->second.addMember(user);

		// str = prefix(user) + "366 " + user->getNickname() + " " + args + " :End of /NAMES list" + SUFFIX;
		// handleSend(client_fd, str);
		// str = prefix(user) + "JOIN :" + args + SUFFIX;
		// handleSend(client_fd, str);
		// str = prefix(user) + "JOIN :" + args + SUFFIX;
		// for (std::vector<User*>::iterator ite = it->second._members.begin(); ite != it->second._members.end(); ite++)
		// 	handleSend((*ite)->getFd(), str);

	}
}
