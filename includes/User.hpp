/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:22:49 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/11 19:15:43 by rpoder           ###   ########.fr       */
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

		void			setNickName(std::string str);
		void			setUsername(std::string str);
		std::string		getNickName() const;
		std::string		getUsername() const;

	private:


		std::string _nickname;
		std::string _username;


};

#endif

