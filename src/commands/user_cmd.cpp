/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/12 18:39:02 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::user_cmd(int client_fd, std::string args)
{
	displayMessage("orange", "[user_cmd function called]");
	User	*user;

	user = this->findUser(client_fd);
	if (user)
		user->setUsername(args);
}