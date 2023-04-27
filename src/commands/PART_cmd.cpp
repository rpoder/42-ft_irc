/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 21:59:23 by mpourrey         ###   ########.fr       */
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
	Channel						*channel;
	ChannelMember				*member;
	std::vector<std::string>	to_quit;
	std::string					reason;


	to_quit = splitChannels(trimChannels(args));
	reason = trimReason(args);
	if (to_quit.size() == 0)
			prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "PART", ""));
	for (std::vector<std::string>::iterator it = to_quit.begin(); it != to_quit.end(); it++)
	{
		channel = findChannel(*it);
		if (channel == NULL)
			prepSend(client_fd, buildErrorMessage(ERR_NOSUCHCHANNEL, user, "PART", *it));
		else
		{
			member = channel->findMember(*user);
			if (member != NULL && member->isOnline() == true)
			{
				channel->prepSendToAll(RPL_PART(user, channel), &Server::prepSend);
				member->setIsOnline(false);
			}
			else
				prepSend(client_fd, buildErrorMessage(ERR_NOTONCHANNEL, user, "PART", *it));
		}
	}
}
