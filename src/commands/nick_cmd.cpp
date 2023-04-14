/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/14 20:19:28 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::nick_cmd(int client_fd, std::string args)
{
	displayMessage("orange", "[nick_cmd function called]");

	User		*user;
	std::string	previous_nickName;
	std::string	str;
	size_t i;

	user = this->findUser(client_fd);
	if (user)
	{
		previous_nickName = user->getNickname();
		user->setNickname(args);
		if (previous_nickName.length() > 0)
		{
			i = user->getUsername().find(" ");
			str = ":" + previous_nickName
				+ "!" + user->getUsername().substr(0, i) + "@localhost "
				+ "NICK :"
				+ user->getNickname() + "\r\n";
			send(client_fd, (char *)str.c_str(), str.length(), 0);
		}
	}
}
