/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:52:17 by rpoder            #+#    #+#             */
/*   Updated: 2023/05/08 15:58:04 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::QUIT_cmd(int fd, User *user, std::string args)
{
	(void) args;

	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
		it->second.deleteMember(user);
	_games.erase(fd);
	_users.erase(fd);
	_input_buf[fd] = "";
	displayMessage("red", "Connection closed");
	close(fd);
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
}
