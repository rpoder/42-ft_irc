/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/15 17:47:51 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::ping_cmd(int client_fd, User *user, std::string args)
{
	std::string	ret;
	std::string tmp;

	displayMessage("orange", "[ping_cmd function called]");
	tmp = "PONG :" + args;
	ret = formatMessage(*user, tmp);
	handleSend(client_fd, ret);
	
}
