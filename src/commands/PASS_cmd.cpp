/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/19 16:17:53 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::PASS_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[PASS_cmd function called]");

	int	nb_args;

	nb_args = countArgs(args);
	if (nb_args < 1)
	{
		handleSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "PASS", ""));
			return ;
	}
	user->setPassword(args);
}
