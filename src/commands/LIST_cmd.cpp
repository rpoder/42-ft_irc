/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:09:15 by caubry            #+#    #+#             */
/*   Updated: 2023/04/26 14:24:31 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void    split_args_list(std::string args, std::vector<std::string> &channels)
{
	size_t comma;
    std::string chan;

    chan = args.substr(0, args.find(" "));
	for (size_t i = 0; i != chan.npos; i++)
	{
		comma = chan.substr(i).find(",");
		if (comma == chan.npos)
		{
			channels.push_back(chan.substr(i));
			return;
		}
		else
			channels.push_back(chan.substr(i, comma));
		i += comma;
	}
}

std::string RPL_LIST(User *user, Channel &channel)
{
	std::string message;

	message = prefix(user) + "322 " + user->getNickname() + " " + channel.getName() + " " + channel.getOnlineMembers() + " :" + SUFFIX;
	return (message);
}

std::string RPL_LISTEND(User *user)
{
	std::string message;

	message = prefix(user) + "323 " + user->getNickname() + " :End of /LIST" + SUFFIX;
	return (message);
}


void    Server::LIST_cmd(int client_fd, User *user, std::string args)
{
    (void) client_fd;
    (void) user;
    (void) args;

    std::vector<std::string> channels;
    if (args.length() > 0)
        split_args_list(args, channels);
    if (channels.size() > 0)
    {
        for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
        {
            Channel *chan;
            chan = findChannel(*it);
            if (chan != NULL)
                handleSend(client_fd, RPL_LIST(user, *chan));
        }
        handleSend(client_fd, RPL_LISTEND(user));
    }
    else
    {
        for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
            handleSend(client_fd, RPL_LIST(user, it->second));
        handleSend(client_fd, RPL_LISTEND(user));
    }
}
