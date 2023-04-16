/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:42:45 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/16 18:02:26 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <User.hpp>
# include <Server.hpp>

class Channel
{
	public:
		Channel();
		Channel(const Channel &copy);
		~Channel();

		Channel	&operator=(const Channel &copy);

	private:
		std::string			_name;
		std::string			_key;
		std::vector<*User>	_members;
		std::vector<*User>	_operators;

		void				addMember(User *user);
		void				deleteMember(User *user);
		void				addOperator(User *user);
		void				deleteOperator(User *user);
};

#endif
