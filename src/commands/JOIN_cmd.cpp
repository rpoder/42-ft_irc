/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:12 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/24 13:47:36 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	fillVectorsJoin(std::string s, std::vector<std::string> &v)
{
	size_t comma;

	std::cout << "string = " << s << std::endl;
	for (size_t i = 0; i != s.npos; i++)
	{
		std::cout << i << " " << s[i] << std::endl;
		comma = s.substr(i).find(",");
		if (comma == s.npos)
		{
			v.push_back(s.substr(i));
			return;
		}
		else
		{
			v.push_back(s.substr(i, comma));
			std::cout << "nom chan ajouté au vector : " << s.substr(i, comma) << std::endl;
		}
		i += comma;
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
	std::cout << "s_channels : " << s_channels << std::endl;
	fillVectorsJoin(s_channels, channels);
	std::cout << "s_key : " << s_keys << std::endl;
	fillVectorsJoin(s_keys, keys);
}

void	Server::JOIN_cmd(int client_fd, User *user, std::string args)
{
	std::map<std::string, Channel>::iterator it;
	std::vector<std::string> channels;
	std::vector<std::string> keys;

	displayMessage("orange", "[JOIN_cmd function called]");

	splitArgsJoin(args, channels, keys);
	for (std::vector<std::string>::iterator ite = channels.begin(); ite != channels.end(); ite++)
	{
		std::string name(*ite);
		if (name[0] != '#')
			sendMessage(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "JOIN", ""));
		else
		{
			it = _channels.find(name);
			// Si le channel n'existe pas, le channel doit etre cree, le membre doit etre cree
			if (it == _channels.end())
			{
				Channel 		newChannel(this, name);
				ChannelMember	newChannelMember(user, true, client_fd);

				printMember(newChannelMember);
				newChannel.addMember(newChannelMember);
				_channels[name] = newChannel;
				std::cout << "Nom du channel crée : " << name << std::endl;
				sendJoinRPL(client_fd, newChannelMember, newChannel);

			}
			else if (it != _channels.end() && it->second.findMember(*user) == NULL) // Si le channel existe mais que le user n'a jamais join le channel
			{
				ChannelMember	newChannelMember(user, false, client_fd);

				it->second.addMember(newChannelMember);
				sendJoinRPL(client_fd, newChannelMember, it->second);

			}
			else // le channel existe, mais le user est deja membre
			{
				ChannelMember	*member;

				member = it->second.findMember(*user);
				member->setIsOnline(true);
				sendJoinRPL(client_fd, *member, it->second);
			}
		}
	}
}

void	Server::sendJoinRPL(int client_fd, ChannelMember &member, Channel &channel)
{

	sendMessage(client_fd, RPL_NAMREPLY(member, channel));
	sendMessage(client_fd, RPL_ENDOFNAMES(member, channel));
	channel.sendToAll(RPL_JOIN(member, channel), &Server::sendMessage);
	//SEND TO ALL
	// for (std::vector<ChannelMember>::iterator it = channel._members.begin(); it != channel._members.end(); it++)
	// 	sendMessage((*it).getFd(), RPL_JOIN(member, channel));
}
