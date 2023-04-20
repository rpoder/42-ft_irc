/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:25 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/18 11:46:39 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <iostream>
# include "User.hpp"
# include "utils.hpp"
# include "Server.hpp"

std::string	RPL_NAMREPLY(ChannelMember &member, Channel &channel);

std::string RPL_ENDOFNAMES(ChannelMember &member, Channel &channel);

std::string RPL_JOIN(ChannelMember &member, Channel &channel);

#endif
