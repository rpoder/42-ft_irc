/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:12:16 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/27 11:25:48 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static bool	isMode(char c)
{
	if (c == 'k' || c == 'b' || c == 'o')
		return (true);
	return (false);
}

static bool	isModeSign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

void	Server::MODE_cmd(int client_fd, User *user, std::string args)
{
	std::vector<std::string>	arguments;
	std::string					channel_name;
	char						mode_sign;
	char						mode;
	std::string					option;
	Channel						*channel;
	ChannelMember				*member;
	size_t						sign_pos;

	arguments = splitArgs(args);
	sign_pos = args.find('+');
	if (sign_pos == std::string::npos)
	{
		sign_pos = args.find('-');
		if (sign_pos == std::string::npos)
		{
			prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "MODE", ""));
			return;
		}
	}
	if (arguments.size() == 2 && arguments[1][1] && !isMode(arguments[1][1]))
		return ;
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
							{
								try
								{
									ChannelMember	*banned_member;
									std::string ms(1, mode_sign);
									std::string m(1, mode);
									std::string reply_details = ms + m + " " + option;

									banned_member = channel->banMember(user, option);
									channel->prepSendToAll(RPL_PART(banned_member->getUser(), channel), &Server::prepSend);
									prepSend(client_fd, RPL_CHANNELMODEIS(*member, *channel, reply_details));
								}
								catch(const std::exception &e)
								{
									prepSend(client_fd, e.what());
								}
								break;
							}

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
							case 'k':
								channel->deleteKey(user, option);
								break;
							case 'b':
							{
								try
								{
									ChannelMember	*debanned_member;
									std::string ms(1, mode_sign);
									std::string m(1, mode);
									std::string reply_details = ms + m + " " + option;

									debanned_member = channel->debanMember(user, option);
									prepSend(client_fd, RPL_CHANNELMODEIS(*member, *channel, reply_details));
								}
								catch(const std::exception &e)
								{
									prepSend(client_fd, e.what());
								}
								break;
							}
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
