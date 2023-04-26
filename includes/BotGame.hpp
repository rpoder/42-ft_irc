/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotGame.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:29:48 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 17:31:40 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BotGame_HPP
# define BotGame_HPP

# include	"User.hpp"
# include	<utility>
# include	<iostream>
# include	<sys/types.h>
# include	<stdio.h>
# include	<string.h>
# include	<cstdlib>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<unistd.h>
# include	<cerrno>
# include	<sys/epoll.h>
# include	<sstream>
# include	<cstring>
# include	<vector>
# include	<algorithm>
# include 	<stdlib.h>
# include 	<time.h>

class BotGame
{
	public:
		BotGame();
		BotGame(const BotGame &copy);
		~BotGame();

		BotGame	&operator=(const BotGame &copy);

		int	play(size_t num, std::string &ret);

	private:
		size_t	_num_to_find;
		size_t	_tries;
};

#endif
