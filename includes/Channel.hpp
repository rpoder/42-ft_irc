/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:42:45 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/20 17:56:04 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include "User.hpp"
# include "ChannelMember.hpp"
# include "Server.hpp"

class Server;

class Channel
{
	public:
		Channel();
		Channel(Server *server_instance, std::string name);
		Channel(const Channel &copy);
		~Channel();

		Channel	&operator=(const Channel &copy);
		bool	operator==(const Channel &rhs);

		void				addMember(ChannelMember member);
		void				deleteMember(ChannelMember member);
		// std::string			listMembers();
		void				sendToAll(std::string message, void (Server::*sendMethod)(int, std::string));
		void				sendToAll(std::string message);
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
		Server		*_server_instance;
		// std::vector<User*>	_operators;
};

#include "Server.hpp"

#endif
