/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 14:27:24 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::PASS_cmd(int client_fd, User *user, std::string args)
{
	int	nb_args;

	nb_args = countArgs(args);
	if (nb_args < 1)
	{
		prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "PASS", ""));
			return ;
	}
	user->setPassword(args);
}
