/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:25 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/20 13:24:10 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <iostream>
# include "User.hpp"
# include "utils.hpp"
# include "Server.hpp"

std::string	RPL_NAMREPLY(ChannelMember &member, Channel &channel);
std::string	RPL_PART(User *user, Channel *channel);

std::string RPL_ENDOFNAMES(ChannelMember &member, Channel &channel);

std::string RPL_JOIN(ChannelMember &member, Channel &channel);

#endif
