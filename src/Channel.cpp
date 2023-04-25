/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:43:06 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 20:03:21 by mpourrey         ###   ########.fr       */
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

std::string	Channel::getKey() const
{
	return (_key);
}

void	Channel::setKey(std::string key)
{
	_key = key;
}

std::vector<std::string>	Channel::getBannedMembers() const
{
	return (_bannedMembers);
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

	member = findMember(nickname_to_add);
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

void	Channel::deleteOperator(User *user, std::string nickname_to_delete)
{
	ChannelMember	*member;
	std::string		err;

	member = findMember(nickname_to_delete);
	if (!member)
	{
		err = buildErrorMessage(ERR_NOSUCHNICK, user, "MODE", nickname_to_delete);
		throw(Channel::ChannelException(err));
	}
	else
	{
		member->setIsOperator(false);
	}
}

void	Channel::defineKey(User *user, std::string &key)
{
	std::string	err;

	if (_key.length() == 0)
		_key = key;
	else
	{
		err = buildErrorMessage(ERR_KEYSET, user, "MODE", _name);
		throw(Channel::ChannelException(err));
	}
}

ChannelMember	*Channel::banMember(User *user, std::string nickname_to_ban)
{
	displayMessage("orange", "[banMember function called]");

	ChannelMember	*member;
	std::string		ip_address;
	std::string		err;
	
	member = findMember(nickname_to_ban);
	if (!member)
	{
		err = buildErrorMessage(ERR_NOSUCHNICK, user, "MODE", nickname_to_ban);
		throw(Channel::ChannelException(err));
	}
	else
	{
		ip_address = member->getUser()->getIpAddress();
		for (std::vector<std::string>::iterator it = _bannedMembers.begin(); it != _bannedMembers.end(); it++)
		{
			if (ip_address.compare(*it) == 0)
			{
				err = buildErrorMessage(ERR_NOSUCHNICK, user, "MODE", nickname_to_ban);
				throw(Channel::ChannelException(err));
			}
		}
		_bannedMembers.push_back(ip_address);
		member->setIsOnline(false);
		return (member);
	}
}

ChannelMember	*Channel::debanMember(User *user, std::string nickname_to_deban)
{
	displayMessage("orange", "[debanMember function called]");

	ChannelMember	*member;
	std::string		ip_address;
	std::string		err;
	
	member = findMember(nickname_to_deban);
	if (!member)
	{
		err = buildErrorMessage(ERR_NOSUCHNICK, user, "MODE", nickname_to_deban);
		throw(Channel::ChannelException(err));
	}
	else
	{
		ip_address = member->getUser()->getIpAddress();
		for (std::vector<std::string>::iterator it = _bannedMembers.begin(); it != _bannedMembers.end(); it++)
		{
			if (ip_address.compare(*it) == 0)
			{
				_bannedMembers.erase(it);
				return (member);
			}
		}
		err = buildErrorMessage(ERR_NOSUCHNICK, user, "MODE", nickname_to_deban);
		throw(Channel::ChannelException(err));
	}
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
