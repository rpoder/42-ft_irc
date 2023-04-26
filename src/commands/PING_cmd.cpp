/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 14:27:32 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::PING_cmd(int client_fd, User *user, std::string args)
{
	std::string message;

	message = prefix(user) + "PONG :" + args + SUFFIX;
	prepSend(client_fd, message);
}
