/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:22:49 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/12 16:06:21 by rpoder           ###   ########.fr       */
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
		void			setIsRegistered(bool is_registered);
		bool			getIsRegistered() const;

	private:
		bool		_is_registered;
		std::string _nickname;
		std::string _username;
};

#endif

