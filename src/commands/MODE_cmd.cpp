/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:12:16 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/24 18:33:29 by rpoder           ###   ########.fr       */
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

void	Server::MODE_cmd(int client_fd, User *user, std::string args)
{
	(void)		user;
	(void)		client_fd;
	std::vector<std::string>	arguments;
	std::string					channel_name;
	char						mode;
	std::string					option;
	Channel						*channel;
	ChannelMember				*member;


	arguments = splitArgs(args);
	for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++)
		std::cout << *it << std::endl;
	if (arguments.size() != 3 || arguments[0][0] != '#' || arguments[1][0] != '+' || arguments[1].size() != 2)
	{
		std::cout << "need more params 461" << std::endl;
		return ;
	}
	channel_name = arguments[0];
	mode = arguments[1][1];
	option = arguments[2];
	channel = findChannel(channel_name);
	std::cout << "channel_name = "<< channel_name << std::endl;
	std::cout << "mode = "<<mode << std::endl;
	std::cout << "option = " << option << std::endl;
	if (!channel)
	{
		std::cout << "no such channel 403" << std::endl;
		return ;
	}
	else
	{
		member = channel->findMember(*user);
		if (!member)
		{
			std::cout << "not on channel 442" << std::endl;
			return ;
		}
		else
		{
			if (member->isOperator() == false)
			{
				std::cout << "your not channel op 482" << std::endl;
				return ;
			}
			else
			{
				try
				{
					switch (mode)
					{
						case 'o':
							channel->defineOperator(user, option);
							break;

						case 'k':
							/* code */
							break;

						case 'b':
							/* code */
							break;

						default:
						{
							std::cout << "no such mode 472" << std::endl;
							return ;
						}
					}
				}
				catch(const std::exception &e)
				{
					std::cout << e.what() << std::endl;
				}

			}
		}
	}



}
