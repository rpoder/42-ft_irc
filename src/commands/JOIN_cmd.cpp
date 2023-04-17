/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 15:10:21 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::JOIN_cmd(int client_fd, User *user, std::string args)
{
	(void) client_fd;
	std::string str;
	std::map<std::string, Channel>::iterator it;
	Channel newChannel(args);

	displayMessage("orange", "[JOIN_cmd function called]");

	if (args[0] != '#')
		handleSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "JOIN", ""));
	else
	{
		it = _channels.find(args);
		if (it == _channels.end())
		{
			newChannel.addOperator(user);
			newChannel.addMember(user);
			std::cout << "Membres new channel " << newChannel.listMembers() << std::endl;
			_channels[args] = newChannel;
		}
		else
			it->second.addMember(user);
		it = _channels.find(args);
		str = prefix(*user) + "353 " + user->getNickname() + " = " + args + " :@" + it->second.listMembers() + SUFFIX;
		handleSend(client_fd, str);
		str = prefix(*user) + "366 " + user->getNickname() + " " + args + " :End of /NAMES list" + SUFFIX;
		handleSend(client_fd, str);
		str = prefix(*user) + "JOIN :" + args + SUFFIX;
		handleSend(client_fd, str);
		str = prefix(*user) + "JOIN :" + args + SUFFIX;
		for (std::vector<User*>::iterator ite = it->second._members.begin(); ite != it->second._members.end(); ite++)
			handleSend((*ite)->getFd(), str);

	}
}
