/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/27 12:47:29 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::NICK_cmd(int client_fd, User *user, std::string args)
{
	std::string						previous_nickName;
	std::string						message;
	int								nb_args;
	std::map<int, User>::iterator	it;
	std::string						tmp;

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
	previous_nickName = user->getNickname();
	args = args.substr(0, args.find(" "));
	if ((findUser(args) || args.compare("bot") == 0) && previous_nickName.length() == 0)
	{
		tmp = args;
		while (findUser(tmp) || tmp.compare("bot") == 0)
			tmp = "_" + tmp;
		user->setNickname(tmp);
		return ;
	}
	else if (findUser(args) || args.compare("bot") == 0)
	{
		prepSend(client_fd, buildErrorMessage(ERR_NICKNAMEINUSE, user, "NICK", args));
		return;
	}
	if (previous_nickName.length() > 0)
	{
		message = prefix(user) + "NICK :" + args + SUFFIX;
		user->setNickname(args);
		prepSend(client_fd, message);
	}
	else
	{
		user->setNickname(args);
	}
}

