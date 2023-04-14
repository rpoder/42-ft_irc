/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:22:49 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/14 17:52:26 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>

class User
{
	public:
		User();
		User(const User &copy);
		~User();

		User	&operator=(const User &copy);

		void			setNickname(std::string &str);
		std::string		getNickname() const;
		void			setUsername(std::string &str);
		std::string		getUsername() const;
		void			setPassword(std::string &str);
		std::string		getPassword() const;
		void			setIsRegistered(bool is_registered);
		bool			getIsRegistered() const;

	private:
		bool		_is_registered;
		std::string _nickname;
		std::string _username;
		std::string	_password;
};

#endif

