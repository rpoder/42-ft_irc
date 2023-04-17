/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 17:20:04 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::NICK_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[NICK_cmd function called]");

	std::string	previous_nickName;
	std::string	message;
	std::map<int, User>::iterator it;

	if (countArgs(args) < 1)
	{
		handleSend(client_fd, buildErrorMessage(ERR_NONICKNAMEGIVEN, user, "NICK", ""));
		return ;
	}
	previous_nickName = user->getNickname();
	for (it = _users.begin(); it != _users.end(); it ++)
	{
		if (it->second.getNickname().compare(args) == 0)
		{
			if (previous_nickName.length() == 0)
				previous_nickName = '*';
			handleSend(client_fd, buildErrorMessage(ERR_NICKNAMEINUSE, user, "NICK", ""));
			// throw (std::exception());
			return ;
		}
	}
	if (previous_nickName.length() > 0)
	{
		message = prefix(user) + "NICK :" + args + SUFFIX;
		user->setNickname(args);
		handleSend(client_fd, message);
	}
	else
	{
		user->setNickname(args);
	}
}
