/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.cpp										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rpoder <rpoder@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/11 19:26:03 by rpoder			#+#	#+#			 */
/*   Updated: 2023/04/12 12:38:56 by rpoder		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "utils.hpp"
#include "Server.hpp"

void	printContainer(std::map<int, User> container)
{
	for (std::map<int, User>::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << it->first << ": " << it->second.getNickname() << " ";
	}
	std::cout << std::endl;
}

void	printUser(int fd, User &user)
{
	std::cout << "\033[1;32m----- New user registered on fd " << fd << " -----" << std::endl;
	std::cout << "Is_registered: " << (user.getIsRegistered() == true ? "true" : "false") << std::endl;
	std::cout << "Nickname: " << user.getNickname() << std::endl;
	std::cout << "Username: " << user.getUsername() << std::endl;
	std::cout << "---------------------------------------\033[0m\n";

}

std::string	trimArgs(std::string str)
{
	size_t	i;

	i = str.find("\r");
	return (str.substr(0, i));
}

void	displayMessage(std::string color, std::string str)
{
	displayMessage(color, str, true);
}

void	displayMessage(std::string color, std::string str, bool endl)
{
	size_t i;

	i = 0;
	std::string colors[6] = {"red", "green", "blue", "orange", "white", "magenta"};
	while (i < 6)
	{
		if (color == colors[i])
			break;
		i++;
	}
	switch (i)
	{
		case 0:
			std::cout << "\033[1;31m" << str << "\033[0m";
			break;
		case 1:
			std::cout << "\033[1;32m" << str << "\033[0m";
			break;
		case 2:
			std::cout << "\033[1;36m" << str << "\033[0m";
			break;
		case 3:
			std::cout << "\033[1;33m" << str << "\033[0m";
			break;
		case 4:
			std::cout << "\033[1;37m" << str << "\033[0m";
			break;
		case 5:
			std::cout << "\033[1;35m" << str << "\033[0m";
			break;
	}
	if (endl == true)
		std::cout << std::endl;
}

int		checkPortNumber(std::string port)
{
	int	port_number;

	for (std::string::iterator it = port.begin(); it != port.end(); it++)
	{
		if (!std::isdigit(*it))
		{
			displayMessage("red","First arg must be a port number.");
			throw (Server::ServerInitException());
		}
	}

	port_number = std::atoi(port.c_str());
	// A voir sio on verifie le port ici ou a l'instanciation du Server
	// if (port_number < PORT_MIN || port_number > PORT_MAX)
	// 	throw (Server::ServerInitException());

	return (port_number);
}

std::string	prefix(User user)
{
	std::string	str;

	str = ":" + user.getNickname()
		+ "!" + user.getUsername() + "@localhost ";
	return (str);
}
// CAP LS
// PASS password
// NICK chsimon
// USER 1 2 3 :4


// JOIN #ok

