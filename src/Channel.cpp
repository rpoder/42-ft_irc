/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:43:06 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 12:57:47 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

Channel::Channel()
{}

Channel::Channel(Server *server_instance, std::string name):
	_name(name),
	_key(),
	_mode_k(false),
	_mode_b(false),
	_mode_o(false),
	_server_instance(server_instance)
{}

Channel::Channel(const Channel &copy)
{
	*this = copy;
}

//!-------------------------------DESTRUCTOR------------------------------------

Channel::~Channel()
{}

//!-------------------------------OPERATOR--------------------------------------

Channel	&Channel::operator=(const Channel &copy)
{
	_name = copy._name;
	_key = copy._key;
	_mode_k = copy._mode_k;
	_mode_b = copy._mode_b;
	_mode_o = copy._mode_o;
	_members = copy._members;
	_server_instance = copy._server_instance;
	return(*this);
}

bool	Channel::operator==(const Channel &rhs)
{
	if (_name == rhs._name)
		return (true);
	return (false);
}

//!-------------------------------ACCESSORS-------------------------------------

std::string	Channel::getName() const
{
	return (_name);
}

std::vector<ChannelMember> Channel::getMembers() const
{
	return (_members);
}


//!-------------------------------FUNCTIONS-------------------------------------

void	Channel::addMember(ChannelMember member)
{
	_members.push_back(member);
}

void	Channel::deleteMember(ChannelMember member)
{
	for (std::vector<ChannelMember>::iterator it = _members.begin(); it != _members.end(); it++)
    {
        if (*it == member)
		{
            it = _members.erase(it);
			break ;
		}
    }
}

ChannelMember	*Channel::findMember(User &user)
{
	for (std::vector<ChannelMember>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (*(it->getUser()) == user)
			return (&(*it));
	}
	return (NULL);
}

ChannelMember	*Channel::findMember(std::string nickname)
{
	for (std::vector<ChannelMember>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (it->getUser()->getNickname() == nickname)
			return (&(*it));
	}
	return (NULL);
}

void	Channel::prepSendToAll(std::string message, void (Server::*prepSendMethod)(int, std::string))
{
	(void) prepSendMethod;

	for (std::vector<ChannelMember>::iterator it = _members.begin(); it != _members.end(); it++)
		(_server_instance->*prepSendMethod)((*it).getFd(), message);
}


void	Channel::defineOperator(User *user, std::string nickname_to_add)
{
	ChannelMember	*member;
	std::string		err;

	std::cout << nickname_to_add << std::endl;
	member = findMember(nickname_to_add);
	std::cout << nickname_to_add << std::endl;
	if (!member)
	{
		err = buildErrorMessage(ERR_NOSUCHNICK, user, "MODE", nickname_to_add);
		throw(Channel::ChannelException(err));
	}
	else
	{
		member->setIsOperator(true);
	}
}

void	Channel::defineKey(User *user, std::string &key)
{
	(void) user;
	_key = key;
}

//!-------------------------------EXCEPTIONS------------------------------------

Channel::ChannelException::ChannelException():
	_message()
{}

Channel::ChannelException::ChannelException(std::string message):
	_message(message)
{}

Channel::ChannelException::~ChannelException() throw()
{}

const char	*Channel::ChannelException::what() const throw()
{
	return(_message.c_str());
}
