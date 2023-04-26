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

int	BotGame::play(size_t num, std::string &ret)
{
	std::string			str;
	std::stringstream	ss;

	if (num < 0 || num > 100)
		ret = "Reste concentré, écrit un nombre entre 0 et 100.";
	else if (num < _num_to_find)
		ret = "C'est plus grand.";
	else if (num > _num_to_find)
		ret = "C'est plus petit.";
	else
	{
		ret = "Tu as gagné petit pou !";
		return (2);
	}
	_tries--;
	if (_tries <= 0)
	{
		ss << _num_to_find;
		str = ss.str();
		ret = "Tu as perdu. Bouhhhhhhh. Le nombre à trouver était " + str + ".";
		return (1);
	}
	ss << _tries;
	str = ss.str();
	if (_tries == 1)
		ret += " " + str + " essai restant.";
	else
		ret += " " + str + " essais restants.";
	return (0);
}
