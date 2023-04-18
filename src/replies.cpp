/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:07:01 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/18 11:47:49 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replies.hpp"

std::string	RPL_NAMREPLY(ChannelMember &member, Channel &channel)
{
	std::string	message;
	User		*user;

	user = member.getUser();
	message = prefix(user) + "353 " + user->getNickname() + " = " + channel.getName() + " :";
	for (std::vector<ChannelMember>::iterator it = channel._members.begin(); it != channel._members.end(); it++)
	{
		if (it->isOperator() == true)
			message += "@" + it->getUser()->getNickname() + " ";
	}
	for (std::vector<ChannelMember>::iterator it = channel._members.begin(); it != channel._members.end(); it++)
	{
		if (it->isOperator() == false)
			message +=  it->getUser()->getNickname() + " ";
	}
	message += SUFFIX;
	return (message);
}

std::string RPL_ENDOFNAMES(ChannelMember &member, Channel &channel)
{
	std::string message;
	User		*user;

	user = member.getUser();
	message = prefix(user) + "366 " + user->getNickname() + " " + channel.getName() + " :End of /NAMES list" + SUFFIX;
	return (message);
}

std::string RPL_JOIN(ChannelMember &member, Channel &channel)
{
	std::string message;
	User		*user;

	user = member.getUser();
	message = prefix(user) + "JOIN :" + channel.getName() + SUFFIX;
	return (message);
}