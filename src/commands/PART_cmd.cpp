/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/19 14:29:24 by parallels        ###   ########.fr       */
=======
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:53:35 by caubry            #+#    #+#             */
/*   Updated: 2023/04/18 12:09:27 by caubry           ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

<<<<<<< HEAD
std::vector<std::string>	extractChannels(std::string args)
{
	size_t						stop;
	std::vector<std::string>	to_quit;

	while (args.length() != 0)
	{
		stop = args.find(',');
		if (stop != std::string::npos)
		{
			to_quit.push_back(args.substr(0, stop));
			stop++;
			args = args.substr(stop);
		}
		else
		{
			to_quit.push_back(args);
			break ;
		}
	}
	return (to_quit);
}

void	Server::PART_cmd(int client_fd, User *user, std::string args)
{
	(void) client_fd;
	(void) user;
	Channel	*channel;
	displayMessage("orange", "[PART_cmd function called]");

	size_t	i;
	std::vector<std::string>	to_quit;

	i = args.find(' ');
	if (args[0] != '#' || i != std::string::npos)
		std::cout << ":caubry!1@localhost 461 caubry PART :Not enough parameters" << std::endl;

	to_quit = extractChannels(args);
	for (std::vector<std::string>::iterator it = to_quit.begin(); it != to_quit.end(); it++)
	{
		channel = findChannel(*it);
		if (channel == NULL)
			std::cout << ":caubry!1@localhost 403 caubry #ok :No such channel" << std::endl;
		else
			std::cout << RPL_PART(user, channel) << std::endl;
	}
	// std::cout << "print tab" << std::endl;
	// for (std::vector<std::string>::iterator it = to_quit.begin(); it != to_quit.end(); it++)
	// 	std::cout << "j" << *it << std::endl;
}
=======
void    Server::PART_cmd(int client_fd, User *user, std::string args)
{
    std::string str;
    std::map<std::string, Channel>::iterator it;
    ChannelMember   *member;

    displayMessage("orange", "[PART_cmd function called]");

    it = _channels.find(args.substr(0,5));
    if (it == _channels.end())
        std::cout << "Channel n'existe pas" << std::endl;
    else
    {
        member = it->second.findMember(*user);
        if (member == NULL)
            std::cout << "User n'existe pas" << std::endl;
        else
        {
            member->setIsOnline(false);
            str = prefix(user) + "PART " + args + SUFFIX;
            handleSend(client_fd, str);
        }
    }
}
>>>>>>> master
