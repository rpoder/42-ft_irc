/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/15 18:19:52 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::join_cmd(int client_fd, User *user, std::string args)
{
	(void) client_fd;
	(void) args;
	(void) user;
	// std::string tmp;
	// std::string res;

	displayMessage("orange", "[join_cmd function called]");
	// tmp = " ";
}
