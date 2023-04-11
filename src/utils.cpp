/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:26:03 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/11 19:38:04 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	printContainer(std::map<int, User> container)
{

	for (std::map<int, User>::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << it->first << ": " << it->second.getNickName() << " ";
	}
	std::cout << std::endl;
}


