/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:12:16 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 13:57:52 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string>	splitArgs(std::string args)
{
	std::vector<std::string>	ret;
	size_t						pos;

	pos = 0;
	while (args[pos] && args[pos] == ' ')
		pos++;
	while (pos != std::string::npos)
	{
		pos = args.find(' ', pos);
		if (pos == std::string::npos)
		{
			ret.push_back(ft_trim(args, ' '));
			break;
		}
		ret.push_back(ft_trim(args.substr(0, pos), ' '));
		while (args[pos] && args[pos] == ' ')
			pos++;
		args = args.substr(pos);
		pos = 0;
	}
	return (ret);
}

bool	isMode(char c)
{
	if (c == 'b' || c == 'k' || c == 'o')
		return (true);
	return (false);
}

bool	isModeSign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

void	Server::MODE_cmd(int client_fd, User *user, std::string args)
{
	displayMessage("orange", "[MODE_cmd function called]");
	(void)		user;
	(void)		client_fd;
	std::vector<std::string>	arguments;
	std::string					channel_name;
	char						mode_sign;
	char						mode;
	std::string					option;
	Channel						*channel;
	ChannelMember				*member;

	(void) mode_sign;
	arguments = splitArgs(args);
	for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++)
		std::cout << *it << std::endl;
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
	std::cout << "channel_name = "<< channel_name << std::endl;
	std::cout << "mode_sign = " << mode_sign << std::endl;
	std::cout << "mode = "<< mode << std::endl;
	std::cout << "option = " << option << std::endl;
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
