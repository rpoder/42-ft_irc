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

bool	BotGame::isNewGame()
{
	return (_tries == 7 ? true : false);
}

//!-------------------------------FUNCTIONS-------------------------------------

bool	BotGame::play(size_t num, std::string &ret)
{
	std::string str;
	std::stringstream ss;

	if (num < _num_to_find)
		ret = "C'est plus grand.";
	else if (num > _num_to_find)
		ret = "C'est plus petit.";
	else
	{
		ret = "Tu as gagne petit pou !";
		return (true);
	}
	_tries--;
	if (_tries <= 0)
	{
		ss << _num_to_find;
		str = ss.str();
		ret = "Tu as perdu. Bouhhhhhhh. Le nombre  à trouver était " + str + ".";
		return (true);
	}
	ss << _tries;
	str = ss.str();
	ret += " " + str + " essais restants.";
	return (false);
}
