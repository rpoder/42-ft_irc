/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/21 11:02:35 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::USER_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[USER_cmd function called]");

	size_t							space_pos;
	std::string						user_name;
	int								nb_args;
	std::map<int, User>::iterator	it;


	nb_args = countArgs(args);
	if (nb_args != 4)
	{
		if (nb_args < 4)
		{
			sendMessage(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "USER", ""));
			return ;
		}
		else
			args = trimArgsNb(args, 4);
	}
	space_pos = args.find(" ");
	user_name = args.substr(0, space_pos);
/* 	for (it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second.getUsername().compare(user_name) == 0)
		{
			sendMessage(client_fd, buildErrorMessage(ERR_ALREADYREGISTRED, user, "USER", ""));
			return ;
		}
	} */
	user->setRawUsername(args);
	user->setUsername(user_name);


	//test
	std::cout << "username set :" << user->getUsername() << std::endl;
	std::cout << "raw_username set :" << user->getRawUsername() << std::endl;

}
