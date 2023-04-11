/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:35:51 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/11 19:16:50 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

User::User():
	_nickname(""),
	_username("")
{

}

User::User(const User &copy)
{
	*this = copy;
}

//!-------------------------------DESTRUCTOR------------------------------------

User::~User()
{

}

//!-------------------------------OPERATOR--------------------------------------

User	&User::operator=(const User &copy)
{
	_nickname = copy._nickname;
	_username = copy._username;
	return (*this);
}

//!-------------------------------ACCESSORS-------------------------------------

void	User::setNickName(std::string str)
{
	_nickname = str;
}

std::string	User::getNickName() const
{
	return (_nickname);
}

void	User::setUsername(std::string str)
{
	_username = str;
}

std::string	User::getUsername() const
{
	return (_username);
}

//!-------------------------------FUNCTIONS-------------------------------------
