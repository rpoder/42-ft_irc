/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:25 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 17:48:36 by mpourrey         ###   ########.fr       */
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

#endif
