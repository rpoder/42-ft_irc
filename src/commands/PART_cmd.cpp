/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:53:35 by caubry            #+#    #+#             */
/*   Updated: 2023/04/18 12:09:27 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void    Server::PART_cmd(int client_fd, User *user, std::string args)
{
    std::string str;
    std::map<std::string, Channel>::iterator it;
    ChannelMember   *member;

    displayMessage("orange", "[PART_cmd function called]");

    it = _channels.find(args.substr(0,5));
    if (it == _channels.end())
        std::cout << "Channel n'existe pas" << std::endl;
    else
    {
        member = it->second.findMember(*user);
        if (member == NULL)
            std::cout << "User n'existe pas" << std::endl;
        else
        {
            member->setIsOnline(false);
            str = prefix(user) + "PART " + args + SUFFIX;
            handleSend(client_fd, str);
        }
    }
}