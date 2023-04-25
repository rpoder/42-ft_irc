/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:12:16 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 16:52:21 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static bool	isModeSign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

void	Server::MODE_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[MODE_cmd function called]");

	std::vector<std::string>	arguments;
	std::string					channel_name;
	char						mode_sign;
	char						mode;
	std::string					option;
	Channel						*channel;
	ChannelMember				*member;

	(void) mode_sign;
	arguments = splitArgs(args);
	if (arguments.size() != 3 || arguments[0][0] != '#' || isModeSign(arguments[1][0]) == false || arguments[1].size() != 2)
	{
		prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "MODE", ""));
		return ;
	}
	channel_name = arguments[0];
	mode_sign = arguments[1][0];
	mode = arguments[1][1];
	option = arguments[2];
	channel = findChannel(channel_name);
	if (!channel)
	{
		prepSend(client_fd, buildErrorMessage(ERR_NOSUCHCHANNEL, user, "MODE", channel_name));
		return ;
	}
	else
	{
		member = channel->findMember(*user);
		if (!member)
		{
			prepSend(client_fd, buildErrorMessage(ERR_NOTONCHANNEL, user, "MODE", option));
			return ;
		}
		else
		{
			if (member->isOperator() == false)
			{
				prepSend(client_fd, buildErrorMessage(ERR_CHANOPRIVSNEEDED, user, "MODE", user->getNickname()));
				return ;
			}
			else
			{
				try
				{
					if (mode_sign == '+')
					{
						switch (mode)
						{
							case 'o':
								channel->defineOperator(user, option);
								break;

							case 'k':
								channel->defineKey(user, option);
								break;

							case 'b':
								/* code */
								break;

							default:
							{
								prepSend(client_fd, buildErrorMessage(ERR_UNKNOWNMODE, user, "MODE", user->getNickname()));
								return ;
							}
						}
					}
					else if (mode_sign == '-')
					{
						switch (mode)
						{
							case 'o':
								channel->deleteOperator(user, option);
								break;

							default:
							{
								prepSend(client_fd, buildErrorMessage(ERR_UNKNOWNMODE, user, "MODE", user->getNickname()));
								return ;
							}
						}
					}
				}
				catch(Channel::ChannelException &e)
				{
					prepSend(client_fd, e.what());
				}
			}
		}
	}
}
