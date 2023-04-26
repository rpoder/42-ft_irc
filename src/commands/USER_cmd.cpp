/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 14:31:01 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::USER_cmd(int client_fd, User *user, std::string args)
{
	size_t							space_pos;
	std::string						user_name;
	std::string						ip_address;
	int								nb_args;
	std::map<int, User>::iterator	it;

	nb_args = countArgs(args);
	if (nb_args != 4)
	{
		if (nb_args < 4)
		{
			prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "USER", ""));
			return ;
		}
		else
			args = trimArgsNb(args, 4);
	}
	space_pos = args.find(" ");
	user_name = args.substr(0, space_pos);
	space_pos = args.find_last_of(" ");
	ip_address = args.substr(space_pos + 1, args.length() - (space_pos + 1));
/*  	for (it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second.getUsername().compare(user_name) == 0)
		{
			prepSend(client_fd, buildErrorMessage(ERR_ALREADYREGISTRED, user, "USER", ""));
			return ;
		}
	} */
	user->setRawUsername(args);
	user->setUsername(user_name);
	//test
	if (user->getNickname().compare("_"))
	{
		std::string s("1.1.1.1");
		user->setIpAddress(s);
	}
	else
		user->setIpAddress(ip_address);
}
