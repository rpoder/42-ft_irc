/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/27 12:48:29 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	fillVectorsJoin(std::string s, std::vector<std::string> &v)
{
	size_t comma;

	for (size_t i = 0; i != s.npos; i++)
	{
		comma = s.substr(i).find(",");
		if (comma == s.npos)
		{
			v.push_back(s.substr(i));
			return;
		}
		else
			v.push_back(s.substr(i, comma));
		i += comma;
	}
}

void	fillVectorsKeys(std::string s, std::vector<std::string> &chan, std::vector<std::string> &keys)
{
	if (s.length() == 0)
	{
		for (size_t i = 0; i < chan.size(); i++)
			keys.push_back("");
	}
	else
	{
		fillVectorsJoin(s, keys);
		if (keys.size() < chan.size())
		{
			for (size_t i = keys.size(); i < chan.size(); i++)
				keys.push_back("");
		}
	}
}

void	splitArgsJoin(std::string args, std::vector<std::string> &channels, std::vector<std::string> &keys)
{
	size_t i;
	size_t j;
	std::string s_channels;
	std::string s_keys;

	i = args.find(" ");
	s_channels = args.substr(0, i);

	if (i != args.npos)
	{
		i++;
		j = args.find(" ");
		s_keys = args.substr(i, j - i);
	}
	fillVectorsJoin(s_channels, channels);
	fillVectorsKeys(s_keys, channels, keys);
}

void	Server::JOIN_cmd(int client_fd, User *user, std::string args)
{
	std::map<std::string, Channel>::iterator it;
	std::vector<std::string> channels;
	std::vector<std::string> keys;

	splitArgsJoin(args, channels, keys);
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string name(channels[i]);
		if (name[0] != '#')
		{
			prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "JOIN", ""));
			break;
		}
		else
		{
			it = _channels.find(name);
			if (it == _channels.end())
			{
				Channel 		newChannel(this, name);
				ChannelMember	newChannelMember(user, true, client_fd);

				newChannel.addMember(newChannelMember);
				if (keys[i].length() > 0 && keys[i].compare("x") != 0)
					newChannel.setKey(keys[i]);
				_channels[name] = newChannel;
				sendJoinRPL(client_fd, newChannelMember, newChannel);

			}
			else if (it != _channels.end() && it->second.findMember(*user) == NULL)
			{
				ChannelMember	newChannelMember(user, false, client_fd);

				if (it->second.getKey().length() > 0 && it->second.getKey().compare(keys[i]) != 0)
					prepSend(client_fd, buildErrorMessage(ERR_BADCHANNELKEY, user, "JOIN", name));
				else
				{
					it->second.addMember(newChannelMember);
					sendJoinRPL(client_fd, newChannelMember, it->second);
				}
			}
			else
			{
				ChannelMember	*member;

				member = it->second.findMember(*user);
				if (it->second.isBannedMember(user->getNickname()))
				{
					prepSend(client_fd, buildErrorMessage(ERR_BANNEDFROMCHAN, user, "JOIN", name));
					return ;
				}

				if (it->second.getKey().length() > 0 && it->second.getKey().compare(keys[i]) != 0)
					prepSend(client_fd, buildErrorMessage(ERR_BADCHANNELKEY, user, "JOIN", name));
				else if (member->isOnline() == false)
				{
					member->setIsOnline(true);
					sendJoinRPL(client_fd, *member, it->second);
				}
			}
		}
	}
}

void	Server::sendJoinRPL(int client_fd, ChannelMember &member, Channel &channel)
{
	prepSend(client_fd, RPL_NAMREPLY(member, channel));
	prepSend(client_fd, RPL_ENDOFNAMES(member, channel));
	channel.prepSendToAll(RPL_JOIN(member, channel), &Server::prepSend);
}
