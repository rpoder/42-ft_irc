/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:35:51 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/16 12:16:38 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

User::User():
	_is_registered(false),
	_nickname(""),
	_username(""),
	_password("")
{}

User::User(const User &copy)
{
	*this = copy;
}

//!-------------------------------DESTRUCTOR------------------------------------

User::~User()
{}

//!-------------------------------OPERATOR--------------------------------------

User	&User::operator=(const User &copy)
{
	_nickname = copy._nickname;
	_username = copy._username;
	_password = copy._password;
	_is_registered = copy._is_registered;
	return (*this);
}

//!-------------------------------ACCESSORS-------------------------------------

void	User::setNickname(std::string &str)
{
	_nickname = str;
}

std::string	User::getNickname() const
{
	return (_nickname);
}

void	User::setUsername(std::string &str)
{
	_username = str;
}

std::string	User::getUsername() const
{
	return (_username);
}

void	User::setRawUsername(std::string &str)
{
	_raw_username = str;
}

std::string	User::getRawUsername() const
{
	return (_raw_username);
}

void	User::setPassword(std::string &str)
{
	_password = str;
}

std::string	User::getPassword() const
{
	return (_password);
}

bool	User::getIsRegistered() const
{
	return (_is_registered);
}

void	User::setIsRegistered(bool is_registered)
{
	_is_registered = is_registered;
}

//!-------------------------------FUNCTIONS-------------------------------------
