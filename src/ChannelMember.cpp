/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMember.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:41:58 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 17:30:38 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelMember.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

ChannelMember::ChannelMember(User *user, bool is_op, int fd):
	_fd(fd),
	_online(true),
	_is_operator(is_op),
	_is_banned(false),
	_user(user)
{}

ChannelMember::ChannelMember(const ChannelMember &copy)
{
	*this = copy;
}

//!-------------------------------DESTRUCTOR------------------------------------

ChannelMember::~ChannelMember()
{}

//!-------------------------------OPERATOR--------------------------------------

ChannelMember	&ChannelMember::operator=(const ChannelMember &copy)
{
	_online = copy._online;
	_is_operator = copy._is_operator;
	_is_banned = copy._is_banned;
	_user = copy._user;
	return(*this);
}

bool	ChannelMember::operator==(const ChannelMember &rhs)
{
	if (_user == rhs._user)
		return (true);
	return (false);
}

//!-------------------------------ACCESSORS-------------------------------------

User	*ChannelMember::getUser() const
{
	return (_user);
}

bool	ChannelMember::isOperator() const
{
	return (_is_operator);
}


//!-------------------------------FUNCTIONS-------------------------------------
