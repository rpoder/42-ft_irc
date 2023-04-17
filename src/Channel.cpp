/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:43:06 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 12:08:21 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

Channel::Channel(std::string name):
	_name(name),
	_key(),
	_mode_k(false),
	_mode_b(false),
	_mode_o(false)
{
}

Channel::Channel(const Channel &copy)
{
	*this = copy;
}

//!-------------------------------DESTRUCTOR------------------------------------

Channel::~Channel()
{

}

//!-------------------------------OPERATOR--------------------------------------

Channel	&Channel::operator=(const Channel &copy)
{
	_name = copy._name;
	_key = copy._key;
	_mode_k = copy._mode_k;
	_mode_b = copy._mode_b;
	_mode_o = copy._mode_o;
	return(*this);
}

//!-------------------------------ACCESSORS-------------------------------------


//!-------------------------------FUNCTIONS-------------------------------------

void	Channel::addMember(User *user)
{
	_members.push_back(user);
}

void	Channel::deleteMember(User *user)
{
	for (std::vector<User*>::iterator it = _members.begin(); it != _members.end(); it++)
    {
        if (*it == user)
		{
            it = _members.erase(it);
			break ;
		}
    }
}

void	Channel::addOperator(User *user)
{
	_operators.push_back(user);
}

void	Channel::deleteOperator(User *user)
{
	for (std::vector<User*>::iterator it = _operators.begin(); it != _operators.end(); it++)
    {
        if (*it == user)
		{
            it = _operators.erase(it);
			break ;
		}
    }
}
