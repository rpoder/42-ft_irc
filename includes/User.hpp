/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:22:49 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 12:12:15 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include	<iostream>
# include	<iostream>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<netdb.h>
# include	<arpa/inet.h>
# include	<netinet/in.h>
# include	<stdio.h>
# include	<string.h>
# include	<cstdlib>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<unistd.h>
# include	<cerrno>
# include	<sys/epoll.h>
# include	<sstream>
# include	<map>

# define FD_UNDEFINED -2

class User
{
	public:
		User();
		User(const User &copy);
		~User();

		User	&operator=(const User &copy);

		bool	operator==(const User &rhs);

		void			setNickname(std::string &str);
		std::string		getNickname() const;
		void			setUsername(std::string &str);
		std::string		getUsername() const;
		void			setRawUsername(std::string &str);
		std::string		getRawUsername() const;
		void			setPassword(std::string &str);
		std::string		getPassword() const;
		void			setIsRegistered(bool is_registered);
		bool			getIsRegistered() const;
		void			setFd(int &fd);
		int				getFd() const;

	private:
		bool		_is_registered;
		std::string _nickname;
		std::string _username;
		std::string _raw_username;
		std::string	_password;
		int			_fd;
};

#endif

