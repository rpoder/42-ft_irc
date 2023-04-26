/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 20:32:22 by mpourrey         ###   ########.fr       */
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
	user->setRawUsername(args);
	user->setUsername(user_name);
}
