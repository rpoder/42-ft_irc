/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/21 11:02:35 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::NICK_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[NICK_cmd function called]");

	std::string						previous_nickName;
	std::string						message;
	int								nb_args;
	std::map<int, User>::iterator	it;

	nb_args = countArgs(args);
	if (nb_args != 1)
	{
		if (nb_args < 1)
		{
			sendMessage(client_fd, buildErrorMessage(ERR_NONICKNAMEGIVEN, user, "NICK", ""));
			return ;
		}
		else
			args = args.substr(0, args.find(" "));
	}
	previous_nickName = user->getNickname();
	if (previous_nickName.length() == 0)
				previous_nickName = '*';
	for (it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second.getNickname().compare(args) == 0)
		{
			sendMessage(client_fd, buildErrorMessage(ERR_NICKNAMEINUSE, user, "NICK", ""));
			return ;
		}
	}
	if (previous_nickName.length() > 0)
	{
		message = prefix(user) + "NICK :" + args + SUFFIX;
		user->setNickname(args);
		sendMessage(client_fd, message);
	}
	else
	{
		user->setNickname(args);
		//std::cout << "nicknqme set to " << user->getNickname() << std::endl;
	}
}
