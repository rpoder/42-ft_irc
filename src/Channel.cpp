/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:43:06 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/16 17:43:09 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

Channel::Channel()
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
	return(*this);
}

//!-------------------------------ACCESSORS-------------------------------------

//!-------------------------------FUNCTIONS-------------------------------------
