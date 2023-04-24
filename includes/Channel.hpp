/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:42:45 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/24 15:53:40 by rpoder           ###   ########.fr       */
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
		void				prepSendToAll(std::string message, void (Server::*sendMethod)(int, std::string));
		ChannelMember		*findMember(User &user);

		std::string							getName() const;
		std::vector<ChannelMember>	getMembers() const;


		// std::vector<User*>	_members;
		std::vector<ChannelMember>	_members;

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
