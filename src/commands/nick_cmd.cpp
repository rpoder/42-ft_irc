/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/15 17:42:17 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::nick_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[nick_cmd function called]");

	std::string	previous_nickName;
	std::string	str;
	std::string	res;

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
