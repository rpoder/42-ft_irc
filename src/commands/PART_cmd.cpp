/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/19 14:29:24 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string>	extractChannels(std::string args)
{
	size_t						i;
	size_t						stop;
	std::vector<std::string>	to_quit;

	i = 0;
	while (args.length() != 0)
	{
		stop = args.find(',');
		if (stop != std::string::npos)
		{
			to_quit.push_back(args.substr(i, stop));
			stop++;
			args = args.substr(stop);
			i = stop;
		}
		else
		{
			to_quit.push_back(args);
			break ;
		}
	}
	return (to_quit);
}

void	PART_cmd(int client_fd, User *user, std::string args)
{
	(void) client_fd;
	(void) user;
	displayMessage("orange", "[PART_cmd function called]");

	size_t	i;
	std::vector<std::string>	to_quit;

	i = args.find(' ');
	if (args[0] != '#' || i != std::string::npos)
		std::cout << "error" << std::endl;

	to_quit = extractChannels(args);
	// std::cout << "print tab" << std::endl;
	// for (std::vector<std::string>::iterator it = to_quit.begin(); it != to_quit.end(); it++)
	// 	std::cout << "j" << *it << std::endl;
}
