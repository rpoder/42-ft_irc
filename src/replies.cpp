/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:07:01 by rpoder            #+#    #+#             */
/*   Updated: 2023/05/07 21:44:10 by mpourrey         ###   ########.fr       */
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

std::string RPL_PART(User *user, Channel *channel, std::string reason)
{
	return (prefix(user) + "PART " + channel->getName() + " :" + reason + SUFFIX);	
}

std::string RPL_PART(User *user, Channel *channel)
{
	return (prefix(user) + "PART :" + channel->getName() + SUFFIX);
}

std::string RPL_KICK(User *user, Channel *channel, User *user_to_kick)
{
	return (prefix(user) + "KICK " + channel->getName() + " " + user_to_kick->getNickname() + SUFFIX);
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
}

std::string RPL_KICK(User *user, Channel *channel, std::string nickname_kicked_out)
{
	std::string message;

	message = prefix(user) + "KICK " + channel->getName() + " " + nickname_kicked_out + SUFFIX;
	return (message);
}

std::string RPL_PRIVMSG_CHANNEL(User *user, Channel &channel, std::string toSent)
{
	std::string message;

	message = prefix(user) + "PRIVMSG " + channel.getName() + " " + toSent + SUFFIX;
	return (message);
}

std::string RPL_PRIVMSG_USER(User *user, User &receiver, std::string toSent)
{
	std::string message;

	message = prefix(user) + "PRIVMSG " + receiver.getNickname() + " " + toSent + SUFFIX;
	return (message);
}

std::string RPL_PRIVMSG_BOT_TO_USER(User &receiver, std::string toSent)
{
	std::string message;

	message = botPrefix() + "PRIVMSG " + receiver.getNickname() + " " + toSent + SUFFIX;
	return (message);
}

std::string RPL_NOTICE_CHANNEL(User *user, Channel &channel, std::string toSent)
{
	std::string message;

	message = prefix(user) + "NOTICE " + channel.getName() + " " + toSent + SUFFIX;
	return (message);
}

std::string RPL_NOTICE_USER(User *user, User &receiver, std::string toSent)
{
	std::string message;

	message = prefix(user) + "NOTICE " + receiver.getNickname() + " " + toSent + SUFFIX;
	return (message);
}

