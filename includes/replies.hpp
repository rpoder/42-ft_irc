/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:25 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 19:27:27 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <iostream>
# include "User.hpp"
# include "utils.hpp"
# include "Server.hpp"

class Channel;

std::string	RPL_NAMREPLY(ChannelMember &member, Channel &channel);

std::string	RPL_PART(User *user, Channel *channel);

std::string RPL_ENDOFNAMES(ChannelMember &member, Channel &channel);

std::string RPL_JOIN(ChannelMember &member, Channel &channel);

std::string	RPL_CHANNELMODEIS(ChannelMember &member, Channel &channel,std::string reply_details);

std::string RPL_KICK(User *user, Channel *channel, std::string nickname_kicked_out);

std::string RPL_PRIVMSG_USER(User *user, User &receiver, std::string toSent);

std::string RPL_PRIVMSG_BOT_TO_USER(User &receiver, std::string toSent);

std::string RPL_PRIVMSG_CHANNEL(User *user, Channel &channel, std::string toSent);

std::string RPL_NOTICE_CHANNEL(User *user, Channel &channel, std::string toSent);

std::string RPL_NOTICE_USER(User *user, User &receiver, std::string toSent);

#endif
