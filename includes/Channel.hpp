/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:42:45 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 15:10:02 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include "User.hpp"

class Server;

class Channel
{
	public:
		// Channel();
		Channel(std::string name = "");
		Channel(const Channel &copy);
		~Channel();

		Channel	&operator=(const Channel &copy);

		void				addMember(User *user);
		void				deleteMember(User *user);
		void				addOperator(User *user);
		void				deleteOperator(User *user);
		std::string			listMembers();
		void				sendToAll(std::string message);

		std::vector<User*>	_members;
		
	private:


		std::string			_name;
		std::string			_key;
		bool				_mode_k;
		bool				_mode_b;
		bool				_mode_o;
		std::vector<User*>	_operators;
};

#include "Server.hpp"

#endif
