/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/16 14:41:47 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::JOIN_cmd(int client_fd, User *user, std::string args)
{
	(void) client_fd;
	(void) args;
	(void) user;
	// std::string tmp;
	// std::string res;

	displayMessage("orange", "[JOIN_cmd function called]");
	// tmp = " ";
}
