/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG_cmd.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:29:41 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 14:29:41 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::playBot(User *user, int fd, std::string message)
{
	std::vector<std::string>	arguments;
	BotGame						*game;
	std::string					ret;
	std::string					old_nickname;
	int							game_ret;


	game = findGame(fd);
	arguments = splitArgs(message);
	if (arguments.size() != 1)
		return ;
	message = message.substr(1);
	if (message == "play" && game == NULL)
	{
		BotGame	new_game;
		_games[fd] = new_game;
		prepSend(fd, RPL_PRIVMSG_BOT_TO_USER(*user, "A toi de jouer ! Envoie un nombre entre 0 et 100."));
	}
	else if (game != NULL && isDigit(message) == true)
	{
		game_ret = game->play(atoi(message.c_str()), ret);
		if (game_ret == 2)
			_games.erase(fd);
		else if (game_ret == 1)
		{
			old_nickname = user->getNickname();
			message = prefix(user) + "NICK :" + old_nickname + "_loser" + SUFFIX;
			user->setNickname(old_nickname + "_loser");
			prepSend(fd, message);
			_games.erase(fd);
		}
		prepSend(fd, RPL_PRIVMSG_BOT_TO_USER(*user, ret));
	}
	else
		prepSend(fd, RPL_PRIVMSG_BOT_TO_USER(*user, "On joue pas comme ca petit pou."));
}

void	Server::PRIVMSG_cmd(int client_fd, User *user, std::string args)
{
	std::string		destinataire;
	std::string		message;
	Channel			*chan;
	ChannelMember	*sender;
	User			*receiver;
	int				receiver_fd;

	receiver_fd = 0;
	destinataire = splitArgsPRIVMSG(args, message);
	chan = findChannel(destinataire);
	receiver = findUser(destinataire);
	if (destinataire.empty())
		prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "PRIVMSG", ":Not enough parameters"));
	else
	{
		if (destinataire[0] == '#' && chan == NULL)
			prepSend(client_fd, buildErrorMessage(ERR_CANNOTSENDTOCHAN, user, "PRIVMSG", destinataire));
		else if (destinataire[0] == '#')
		{
			sender = chan->findMember(*user);
			if (sender == NULL || (sender != NULL && sender->isOnline() == false))
				prepSend(client_fd, buildErrorMessage(ERR_CANNOTSENDTOCHAN, user, "PRIVMSG", destinataire));
			else
				chan->prepSendToAll(RPL_PRIVMSG_CHANNEL(user, *chan, message), &Server::prepSend, sender);
		}
		else if (destinataire == "bot")
			playBot(user, client_fd, message);
		else if (receiver == NULL)
			prepSend(client_fd, buildErrorMessage(ERR_NOSUCHNICK, user, "PRIVMSG", destinataire));
		else
		{
			for (std::map<int,User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if (it->second == *receiver)
				{
					receiver_fd = it->first;
					break;
				}
			}
			if (receiver_fd == 0)
				prepSend(client_fd, buildErrorMessage(ERR_NOSUCHNICK, user, "PRIVMSG", args.substr(0, args.find(' '))));
			else
				prepSend(receiver_fd, RPL_PRIVMSG_USER(user, *receiver, message));
		}
	}
}
