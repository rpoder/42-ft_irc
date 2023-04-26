/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotGame.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:29:25 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 17:29:29 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BotGame.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

BotGame::BotGame():
	_tries(7)
{
	srand (time(NULL));
	_num_to_find = rand() % 100;
}

BotGame::BotGame(const BotGame &copy)
{
	*this = copy;
}

//!-------------------------------DESTRUCTOR------------------------------------

BotGame::~BotGame()
{

}

//!-------------------------------OPERATOR--------------------------------------

BotGame	&BotGame::operator=(const BotGame &copy)
{
	_num_to_find = copy._num_to_find;
	_tries = copy._tries;
	return(*this);
}

//!-------------------------------ACCESSORS-------------------------------------

//!-------------------------------FUNCTIONS-------------------------------------

bool	BotGame::play(size_t num, std::string &ret)
{
	std::string str;
	std::stringstream ss;

	if (num > _num_to_find)
		ret = "It's lower.";
	else if (num < _num_to_find)
		ret = "It's upper.";
	else
	{
		ret = "You won !";
		return (true);
	}
	_tries--;
	if (_tries <= 0)
	{
		ret = "You lost. Bouhhhhhhh";
		return (true);
	}
	ss << _tries;
	str = ss.str();
	ret += "\n" + str + "tries left.";
	return (false);
}
