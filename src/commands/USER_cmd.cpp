/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 17:19:25 by mpourrey         ###   ########.fr       */
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
 	for (it = _users.begin(); it != _users.end(); it++)
	{
		std::cout << "compare" << ip_address << "to ip : |" << it->second.getIpAddress() << "|" << std::endl;
		std::cout << "compare to name : |"<< it->second.getUsername() << "|" << std::endl;
		
		if (it->second.getUsername().compare(user_name) == 0 || it->second.getIpAddress().compare(ip_address) == 0)
		{
			prepSend(client_fd, buildErrorMessage(ERR_ALREADYREGISTRED, user, "USER", ""));
			return ;
		}
	}
	user->setRawUsername(args);
	user->setUsername(user_name);
	user->setIpAddress(ip_address);
}
