/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 11:21:01 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void            fillVectorsJoin(std::string s, std::vector<std::string> &v)
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

void            splitArgsJoin(std::string args, std::vector<std::string> &channels, std::vector<std::string> &keys)
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
	fillVectorsJoin(s_keys, keys);
}

void	Server::JOIN_cmd(int client_fd, User *user, std::string args)
{
	std::map<std::string, Channel>::iterator it;
	std::vector<std::string> channels;
	std::vector<std::string> keys;

	displayMessage("orange", "[JOIN_cmd function called]");

	splitArgsJoin(args, channels, keys);
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string name(channels[i]);
		if (name[0] != '#')
		{
			handleSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "JOIN", ""));
			break;
		}
		else
		{
			it = _channels.find(name);
			// Si le channel n'existe pas, le channel doit etre cree, le membre doit etre cree
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
			else if (it != _channels.end() && it->second.findMember(*user) == NULL) // Si le channel existe mais que le user n'a jamais join le channel
			{
				ChannelMember	newChannelMember(user, false, client_fd);

				if (it->second.getKey().length() > 0 && it->second.getKey().compare(keys[i]) != 0)
					handleSend(client_fd, buildErrorMessage(ERR_BADCHANNELKEY, user, "JOIN", name));
				else
				{
					it->second.addMember(newChannelMember);
					sendJoinRPL(client_fd, newChannelMember, it->second);
				}
			}
			else // le channel existe, mais le user est deja membre
			{
				ChannelMember	*member;

				member = it->second.findMember(*user);

				//parcourir tableau de bannis et return si trouve
				std::vector<std::string>	banned_list;

				banned_list = it->second.getBannedMembers();
				for (std::vector<std::string>::iterator it = banned_list.begin(); it != banned_list.end(); it++)
				{
					if (user->getIpAddress().compare(*it) == 0)
					{
						handleSend(client_fd, buildErrorMessage(ERR_BANNEDFROMCHAN, user, "JOIN", name));
						return ;
					}
				}
				if (it->second.getKey().length() > 0 && it->second.getKey().compare(keys[i]) != 0)
					handleSend(client_fd, buildErrorMessage(ERR_BADCHANNELKEY, user, "JOIN", name));
				else
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
	handleSend(client_fd, RPL_NAMREPLY(member, channel));
	handleSend(client_fd, RPL_ENDOFNAMES(member, channel));
	channel.prepSendToAll(RPL_JOIN(member, channel), &Server::prepSend);
}
