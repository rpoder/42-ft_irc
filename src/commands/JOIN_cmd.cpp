/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 13:06:12 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::JOIN_cmd(int client_fd, User *user, std::string args)
{
	(void) client_fd;
	(void) args;
	(void) user;
	std::string str;
	// std::string tmp;
	// std::string res;

	displayMessage("orange", "[JOIN_cmd function called]");
	// tmp = " ";


	if (args[0] != '#')
		handleSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "JOIN", ""));
	else
	{
		str = prefix(*user) + "353 " + user->getNickname() + " = " + args + " :@" + user->getNickname() + SUFFIX;
		handleSend(client_fd, str);
		str = prefix(*user) + "366 " + user->getNickname() + " " + args + " :End of /NAMES list" + SUFFIX;
		handleSend(client_fd, str);
		str = prefix(*user) + "JOIN :" + args + SUFFIX;
		handleSend(client_fd, str);
	}
}
