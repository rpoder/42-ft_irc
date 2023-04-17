/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:42:45 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/17 13:13:33 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <User.hpp>

class Channel
{
	public:
		Channel(std::string name);
		Channel(const Channel &copy);
		~Channel();

		Channel	&operator=(const Channel &copy);

		void				addMember(User *user);
		void				deleteMember(User *user);
		void				addOperator(User *user);
		void				deleteOperator(User *user);


	private:

		Channel();

		std::string			_name;
		std::string			_key;
		bool				_mode_k;
		bool				_mode_b;
		bool				_mode_o;
		std::vector<User*>	_members;
		std::vector<User*>	_operators;
};

#endif
