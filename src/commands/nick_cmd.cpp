/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/16 11:31:25 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::nick_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[nick_cmd function called]");

	std::string	previous_nickName;
	std::string	str;
	std::string	res;
	std::map<int, User>::iterator it;

	for (it = _users.begin(); it != _users.end(); it ++)
	{
		if (it->second.getNickname().compare(args) == 0)
		{
			std::cout << ERR_NICKNAMEINUSE << " : Nickname already in use" << std::endl;
			return;
		}
	}
	else
	{
		previous_nickName = user->getNickname();
		if (previous_nickName.length() > 0)
		{
			str =  + "NICK :" + args;
			res = formatMessage(*user, str);
			std::cout << res << std::endl;
			user->setNickname(args);
			handleSend(client_fd, res);
			// send(client_fd, (char *)str.c_str(), str.length(), 0);
		}
		else
			user->setNickname(args);
	}
}
