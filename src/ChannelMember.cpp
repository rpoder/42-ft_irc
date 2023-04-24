/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMember.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:41:58 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/24 18:03:20 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelMember.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

ChannelMember::ChannelMember(User *user, bool is_op, int fd):
	_fd(fd),
	_is_online(true),
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
	_fd = copy._fd;
	_is_online = copy._is_online;
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

void	ChannelMember::setIsOperator(bool is_operator)
{
	_is_operator = is_operator;
}

void	ChannelMember::setIsOnline(bool is_online)
{
	_is_online = is_online;
}

bool	ChannelMember::isOnline() const
{
	return (_is_online);
}

int		ChannelMember::getFd()
{
	return (_fd);
}

//!-------------------------------FUNCTIONS-------------------------------------
