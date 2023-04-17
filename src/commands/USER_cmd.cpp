/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/16 22:29:31 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::USER_cmd(int client_fd, User *user, std::string args)
{
	(void) client_fd;
	displayMessage("orange", "[USER_cmd function called]");
	size_t		i;
	std::string	tmp;

	i = args.find(" ");
	if (i != std::string::npos)
	{
		tmp = args.substr(0, i);
		user->setUsername(tmp); //verifier 
	}
	else
		user->setUsername(args);
	user->setRawUsername(args);

	//test
	std::cout << "username set :" << user->getUsername() << std::endl;
	std::cout << "raw_username set :" << user->getRawUsername() << std::endl;

}
