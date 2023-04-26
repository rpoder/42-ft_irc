/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:47:32 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 17:16:32 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_TPP
# define UTILS_TPP

# include <iostream>
# include "User.hpp"
# include "Server.hpp"
# include "ChannelMember.hpp"
# include <map>
# include <sstream>
# include <vector>

void						printContainer(std::map<int, User> container);
void						printUser(int fd, User &user);
void						printMember(ChannelMember member);


// void						executeCommand(std::string cmd, int client_fd);


std::string					trimInput(std::string str);

void						displayMessage(std::string color, std::string str);
void						displayMessage(std::string color, std::string str, bool endl);

int							checkPortNumber(std::string port);

std::string					buildErrorMessage(int code, User *user, std::string cmd, std::string args);

std::string					prefix(User *user);

size_t						countArgs(std::string args);
std::string					trimArgsNb(std::string args, int nb);

std::string					ft_trim(std::string str, char c);

std::vector<std::string>	splitArgs(std::string args);

std::string	                splitArgsPRIVMSG(std::string args, std::string &message);

#endif
