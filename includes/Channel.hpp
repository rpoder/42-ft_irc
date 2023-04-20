/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:42:45 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/18 12:25:10 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include "User.hpp"
# include "ChannelMember.hpp"

class Server;

class Channel
{
	public:
		// Channel();
		Channel(std::string name = "");
		Channel(const Channel &copy);
		~Channel();

		Channel	&operator=(const Channel &copy);

		void				addMember(ChannelMember member);
		void				deleteMember(ChannelMember member);
		// std::string			listMembers();
		// void				sendToAll(std::string message);
		ChannelMember		*findMember(User &user);

		std::string			getName() const;


		std::vector<ChannelMember>	_members;
		// std::vector<User*>	_members;

	private:
		std::string	_name;
		std::string	_key;
		bool		_mode_k;
		bool		_mode_b;
		bool		_mode_o;
		// std::vector<User*>	_operators;
};

#include "Server.hpp"

#endif
