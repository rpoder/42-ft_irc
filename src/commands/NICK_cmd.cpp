/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 16:56:30 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::NICK_cmd(int client_fd, User *user, std::string args)
{
	std::string						previous_nickName;
	std::string						message;
	int								nb_args;
	std::map<int, User>::iterator	it;

	nb_args = countArgs(args);
	if (nb_args != 1)
	{
		if (nb_args < 1)
		{
			std::string	nick = "*";

			user->setNickname(nick);
			prepSend(client_fd, buildErrorMessage(ERR_NONICKNAMEGIVEN, user, "NICK", ""));
			nick = "";
			user->setNickname(nick);
			return ;
		}
		else
			args = args.substr(0, args.find(" "));
	}
	for (it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second.getNickname().compare(args) == 0)
		{
			prepSend(client_fd, buildErrorMessage(ERR_NICKNAMEINUSE, user, "NICK", ""));
			return ;
		}
	}
	previous_nickName = user->getNickname();
	if (previous_nickName.length() > 0)
	{
		message = prefix(user) + "NICK :" + args + SUFFIX;
		user->setNickname(args);
		prepSend(client_fd, message);
	}
	else
		user->setNickname(args);
}

