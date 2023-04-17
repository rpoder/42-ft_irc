/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMember.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:41:33 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 17:32:06 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMEMBER_HPP
# define CHANNELMEMBER_HPP

# include "User.hpp"

class ChannelMember
{
	public:
		ChannelMember(User *user, bool is_op, int fd);
		ChannelMember(const ChannelMember &copy);
		~ChannelMember();

		ChannelMember	&operator=(const ChannelMember &copy);
		bool			operator==(const ChannelMember &rhs);

		User			*getUser() const;
		bool			isOperator() const;


	private:
		ChannelMember();

		int		_fd;
		bool	_online;
		bool	_is_operator;
		bool	_is_banned;
		User	*_user;
};

#endif
