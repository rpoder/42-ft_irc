/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:00:05 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/24 15:40:22 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

Message::Message()
{

}

Message::Message(Server *server) :
	_server_instance(server)
{

}

Message::Message(const Message &copy)
{
	*this = copy;
}

//!-------------------------------DESTRUCTOR------------------------------------

Message::~Message()
{

}

//!-------------------------------OPERATOR--------------------------------------

Message	&Message::operator=(const Message &copy)
{
	_messages = copy._messages;
	return(*this);
}

//!-------------------------------ACCESSORS-------------------------------------

//!-------------------------------FUNCTIONS-------------------------------------

void	Message::addMessage(int fd, std::string message)
{
	std::pair<int, std::string> pair;

	pair.first = fd;
	pair.second = message;
	_messages.push_back(pair);
}


void	Message::sendTo(int fd, void (Server::*sendMethod)(int, std::string))
{
	std::vector< std::pair<int, std::string> >::iterator it;

	it = _messages.begin();
	while (it != _messages.end())
	{
		if (it->first == fd)
		{
			(_server_instance->*sendMethod)(fd, it->second);
			_messages.erase(it);
		}
		else
			it++;
	}
}
