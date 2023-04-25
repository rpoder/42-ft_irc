/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:07:01 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 18:21:51 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replies.hpp"

std::string	RPL_NAMREPLY(ChannelMember &member, Channel &channel)
{
	std::string	message;
	std::vector<ChannelMember> members;
	User		*user;

	members = channel.getMembers();
	user = member.getUser();
	message = prefix(user) + "353 " + user->getNickname() + " = " + channel.getName() + " :";
	for (std::vector<ChannelMember>::iterator it = members.begin(); it != members.end(); it++)
	{
		if (it->isOperator() == true)
			message += "@" + it->getUser()->getNickname() + " ";
	}
	for (std::vector<ChannelMember>::iterator it = members.begin(); it != members.end(); it++)
	{
		if (it->isOperator() == false)
			message +=  it->getUser()->getNickname() + " ";
	}
	message += SUFFIX;
	return (message);
}

std::string RPL_PART(User *user, Channel *channel)
{
	return (prefix(user) + "PART :" + channel->getName() + SUFFIX);
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

std::string	RPL_CHANNELMODEIS(ChannelMember &member, Channel &channel, std::string reply_details)
{
	std::string message;
	User		*user;

	user = member.getUser();
	message = prefix(user) + "324 " + user->getNickname() + " " + channel.getName() + " " +
		reply_details + SUFFIX;
	return (message);
/* 
			:caubry!1@localhost 324 caubry #test +np
		:rpoder!1@localhost 324 rpoder #coucou +o rpoder
		:rpoder!1@localhost 324 rpoder #coucou +n */
}
