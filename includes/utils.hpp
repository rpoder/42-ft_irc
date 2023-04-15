/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.hpp										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rpoder <rpoder@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/11 19:37:31 by rpoder			#+#	#+#			 */
/*   Updated: 2023/04/12 12:39:53 by rpoder		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef UTILS_TPP
# define UTILS_TPP

# include <iostream>
# include "User.hpp"
# include <map>
# include <sstream>

void	    printContainer(std::map<int, User> container);

void	    executeCommand(std::string cmd, int client_fd);

void	    printUser(int fd, User &user);

std::string	trimArgs(std::string str);

void	    displayMessage(std::string color, std::string str);
void	    displayMessage(std::string color, std::string str, bool endl);

int        checkPortNumber(std::string port);

std::string	formatMessage(User user, std::string &message);

#endif
