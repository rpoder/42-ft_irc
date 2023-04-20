/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/20 18:03:40 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string	trimReason(std::string str)
{
	size_t	pos;

	pos = str.find(':');
	if (pos != std::string::npos)
		return (ft_trim(str.substr(pos + 1), ' '));
	return ("");
}

std::string	trimChannels(std::string str)
{
	size_t	pos;

	pos = str.find(':');
	if (pos != std::string::npos)
		return (str.substr(0, pos));
	return (str);
}

std::vector<std::string>	splitChannels(std::string args)
{
	size_t						stop;
	std::vector<std::string>	to_quit;

	std::cout << args << std::endl;
	while (args.length() != 0)
	{
		stop = args.find(',');
		if (stop != std::string::npos)
		{
			if (args[0] && args[0] == '#')
				to_quit.push_back(args.substr(0, stop));
			stop++;
			while (args[stop] == ' ')
				stop++;
			args = args.substr(stop);
		}
		else
		{
			if (args[0] && args[0] == '#')
			{
				to_quit.push_back(ft_trim(args, ' '));
			}
			break ;
		}
	}
	return (to_quit);
}

void	Server::PART_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[PART_cmd function called]");
	Channel						*channel;
	ChannelMember				*member;
	std::vector<std::string>	to_quit;
	std::string					reason;

	to_quit = splitChannels(trimChannels(args));
	reason = trimReason(args);
	for (std::vector<std::string>::iterator it = to_quit.begin(); it != to_quit.end(); it++)
		std::cout << *it << std::endl;
	if (to_quit.size() == 0)
			handleSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "PART", ""));	
	for (std::vector<std::string>::iterator it = to_quit.begin(); it != to_quit.end(); it++)
	{
		channel = findChannel(*it);
		if (channel == NULL)
			handleSend(client_fd, buildErrorMessage(ERR_NOSUCHCHANNEL, user, "PART", *it));
		else
		{
			member = channel->findMember(*user);
			if (member == NULL)
			{
				std::cout << "not on channel" <<std::endl;	
				handleSend(client_fd, buildErrorMessage(ERR_NOTONCHANNEL, user, "PART", *it));
			}
			else
			{
				member->setIsOnline(false);
				channel->sendToAll(RPL_PART(user, channel), &Server::handleSend);	
			}
		}
	}
}
