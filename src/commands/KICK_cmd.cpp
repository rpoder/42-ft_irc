/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:38:37 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 14:24:26 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::KICK_cmd(int client_fd, User *user, std::string args)
{
	std::string					channel_name;
	std::string					nickname_to_kick;
	std::string					reason;
	std::vector<std::string>	arguments;
	Channel						*channel;
	ChannelMember				*member;
	ChannelMember				*kicked_member;

	arguments = splitArgs(args);
	if ((arguments.size() != 2 && arguments.size() != 3) || arguments[0][0] != '#')
	{
		prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "KICK", ""));
		return ;
	}
	channel_name = arguments[0];
	nickname_to_kick = arguments[1];
	if (arguments.size() == 3)
		reason = arguments[2];
	channel = findChannel(channel_name);
	if (!channel)
	{
		prepSend(client_fd, buildErrorMessage(ERR_NOSUCHCHANNEL, user, "KICK", channel_name));
		return ;
	}
	else
	{
		member = channel->findMember(*user);
		if (!member)
		{
			prepSend(client_fd, buildErrorMessage(ERR_NOTONCHANNEL, user, "KICK", member->getUser()->getNickname()));
			return ;
		}
		else if (member->isOperator() == true)
		{
			try
			{
				kicked_member = channel->kickMember(user, nickname_to_kick);
				prepSend(kicked_member->getFd(), RPL_PART(kicked_member->getUser(), channel));
				channel->prepSendToAll(RPL_KICK(user, channel, nickname_to_kick), &Server::prepSend);
			}
			catch(Channel::ChannelException &e)
			{
				prepSend(client_fd, e.what());
			}
		}
		else if (member->isOperator() == false)
		{
			prepSend(client_fd, buildErrorMessage(ERR_CHANOPRIVSNEEDED, user, "KICK",""));
			return ;
		}
		else
		{
			prepSend(client_fd, buildErrorMessage(ERR_NOSUCHNICK, user, "KICK", member->getUser()->getNickname()));
			return ;
		}
	}
}

