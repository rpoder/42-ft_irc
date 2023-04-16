/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/16 16:59:59 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::NICK_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[NICK_cmd function called]");

	std::string	previous_nickName;
	std::string	message;
	std::map<int, User>::iterator it;

	previous_nickName = user->getNickname();

	if (countArgs(args) != 1)
	{
		handleSend(client_fd, buildErrorMessage(ERR_NONICKNAMEGIVEN, user, "NICK", ""));
		return ;
	}
	for (it = _users.begin(); it != _users.end(); it ++)
	{
		if (it->second.getNickname().compare(args) == 0)
		{
			if (previous_nickName.length() == 0)
				previous_nickName = '*';
			message = ": 433 " + previous_nickName + " " + args + " :Nickname already in use"+ SUFFIX;
			std::cout << message << std::endl;
			handleSend(client_fd, message);
			// throw (std::exception());
			return ;
		}
	}
	if (previous_nickName.length() > 0)
	{
		message = prefix(*user) + "NICK :" + args + SUFFIX;
		user->setNickname(args);
		handleSend(client_fd, message);
	}
	else
		user->setNickname(args);
}
