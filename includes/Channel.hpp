/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:42:45 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 19:55:39 by mpourrey         ###   ########.fr       */
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
		void				defineOperator(User *user, std::string nickname_to_add);
		void				deleteOperator(User *user, std::string nickname_to_delete);
		void				defineKey(User *user, std::string &key);
		ChannelMember		*banMember(User *user, std::string nickname_to_ban);
		ChannelMember		*debanMember(User *user, std::string nickname_to_deban);

		void				deleteMember(ChannelMember member);
		// std::string			listMembers();
		void				prepSendToAll(std::string message, void (Server::*sendMethod)(int, std::string));
		ChannelMember		*findMember(User &user);
		ChannelMember		*findMember(std::string nickname);

		std::string					getName() const;
		std::vector<ChannelMember>	getMembers() const;
		std::string					getKey() const;
		void						setKey(std::string key);
		std::vector<std::string>	getBannedMembers() const;
		
		// std::vector<User*>	_members;
		std::vector<ChannelMember>	_members; //public ??
		class ChannelException:
			public std::exception
		{
			public:
				ChannelException();
				ChannelException(std::string message);
				virtual const char	*what() const throw();
				virtual				~ChannelException() throw();

			private:
				std::string	_message;
		};

	private:
		std::string					_name;
		std::string					_key;
		bool						_mode_k;
		bool						_mode_b;
		bool						_mode_o;
		Server						*_server_instance;
		std::vector<std::string>	_bannedMembers;

		// std::vector<User*>	_operators;
};

#include "Server.hpp"

#endif
