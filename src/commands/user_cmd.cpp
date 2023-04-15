/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/15 17:43:19 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::user_cmd(int client_fd, User *user, std::string args)
{
	(void) client_fd;
	displayMessage("orange", "[user_cmd function called]");
	size_t		i;
	std::string	tmp;

	i = args.find(" ");
	if (i != std::string::npos)
	{
		tmp = args.substr(0, i);
		user->setUsername(tmp);
	}
	else
		user->setUsername(args);
	user->setRawUsername(args);
}
