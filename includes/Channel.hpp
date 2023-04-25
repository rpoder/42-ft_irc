/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:42:45 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 16:55:35 by rpoder           ###   ########.fr       */
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
		ChannelMember		*kickMember(User *user, std::string nickname);

		void				deleteMember(ChannelMember member);
		void				prepSendToAll(std::string message, void (Server::*sendMethod)(int, std::string));
		ChannelMember		*findMember(User &user);
		ChannelMember		*findMember(std::string nickname);

		std::string					getName() const;
		std::vector<ChannelMember>	getMembers() const;
		std::string					getKey() const;
		void						setKey(std::string key);

		std::vector<ChannelMember>	_members;

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
		std::string	_name;
		std::string	_key;
		bool		_mode_k;
		bool		_mode_b;
		bool		_mode_o;
		Server		*_server_instance;
};

#include "Server.hpp"

#endif
