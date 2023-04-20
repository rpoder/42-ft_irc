/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMember.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:41:33 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/20 17:29:10 by margot           ###   ########.fr       */
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
		void			setIsOnline(bool is_online);
		int				getFd();

	private:
		ChannelMember();

		int		_fd;
		bool	_is_online;
		bool	_is_operator;
		bool	_is_banned;
		User	*_user;
};

#endif
