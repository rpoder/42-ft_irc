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

void	printMember(ChannelMember member)
{
	User	user;

	user = *(member.getUser());
	std::cout << "\033[1;36m----- ChannelMember" << " -----" << std::endl;
	std::cout << "fd" << member.getFd() << std::endl;
	std::cout << "Is_online: " << (member.isOnline() == true ? "true" : "false") << std::endl;
	std::cout << "Is_registered: " << (user.getIsRegistered() == true ? "true" : "false") << std::endl;
	std::cout << "Nickname: " << user.getNickname() << std::endl;
	std::cout << "Username: " << user.getUsername() << std::endl;
	std::cout << "---------------------------\033[0m\n";
}

std::string	trimInput(std::string str)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (str[j] && str[j] == ' ')
		j++;
	str = str.substr(j);
	i = str.find('\r');
	if (str[i])
		str = str.substr(0, i);
	return (str);
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
			throw (Server::ServerException());
		}
	}

	port_number = std::atoi(port.c_str());
	return (port_number);
}

std::string	prefix(User *user)
{
	std::string	str;

	str = ":" + user->getNickname()
		+ "!" + user->getUsername() + "@localhost ";
	return (str);
}

std::string	botPrefix()
{
	return (":bot!bot@localhost ");
}

std::string buildErrorMessage(int code, User *user, std::string cmd, std::string args)
{
	std::string			message;
	std::string			code_str;
	std::stringstream	ss;

	ss << code;
	ss >> code_str;

	message = prefix(user) + code_str + " " + user->getNickname();
	if (code == ERR_NEEDMOREPARAMS)
		message += " " + cmd;
	else if (args.length() != 0)
		message += " " + args;
	message += " :";
	switch (code)
	{
		case ERR_NEEDMOREPARAMS:
			message += "Not enough parameters";
			break ;

		case ERR_NONICKNAMEGIVEN:
			message += "No nickname given";
			break ;

		// case ERR_NICKNAMEINUSE:
		// 	message += "Nickname is already in use";
		// 	break ;

		case ERR_ALREADYREGISTRED:
			message += "You may not reregister";
			break ;

		case ERR_NOSUCHCHANNEL:
			message += "No such channel";
			break ;

		case ERR_NOTONCHANNEL:
			message += "You are not on that channel";
			break ;

		case ERR_BANNEDFROMCHAN:
			message += "You are banned from channel";
			break ;

		case ERR_UNKNOWNMODE:
			message += "No such mode";
			break ;

		case ERR_CHANOPRIVSNEEDED:
			message += "You must be operator";
			break ;

		case ERR_NOSUCHNICK:
			message += "No such nickname";
			break ;

		case ERR_CANNOTSENDTOCHAN:
			message += "Cannot send to channel";
			break ;

		case ERR_KEYSET:
			message += "Cannot set key";
			break ;

		case ERR_BADCHANNELKEY:
			message += "Bad channel key";
			break ;

		default:
			break ;
	}
	message += SUFFIX;
	return (message);
}

size_t	countArgs(std::string args)
{
	size_t	count;
	size_t	i;

	i = 0;
	if (args.length() == 0)
		return (0);
	count = 1;
	while (args[i])
	{
		if (args[i] == ' ')
		{
			count++;
			while (args[i] && args[i] == ' ')
				i++;
			if (!args[i])
			{
				count--;
				break;
			}
		}
		i++;
	}
	return (count);
}

std::string	trimArgsNb(std::string args, int nb)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while(count <= nb)
	{
		if (args[i] == ' ')
		{
			count++;
			if (count == nb)
				break;
			while (args[i] && args[i] == ' ')
				i++;
		}
		i++;
	}
	return (args.substr(0, i));
}

std::string ft_trim(std::string str, char c)
{
	size_t	start;
	int		stop;

	start = 0;
	while (str[start] && str[start] == c)
		start++;
	stop = str.length() - 1;
	while (stop >= 0 && str[stop] == c)
		stop--;
	return (str.substr(start, stop - start + 1));
}


std::vector<std::string>	splitArgs(std::string args)
{
	std::vector<std::string>	ret;
	size_t						pos;

	pos = 0;
	while (args[pos] && args[pos] == ' ')
		pos++;
	while (pos != std::string::npos)
	{
		pos = args.find(' ', pos);
		if (pos == std::string::npos)
		{
			ret.push_back(ft_trim(args, ' '));
			break;
		}
		ret.push_back(ft_trim(args.substr(0, pos), ' '));
		while (args[pos] && args[pos] == ' ')
			pos++;
		args = args.substr(pos);
		pos = 0;
	}
	return (ret);
}

std::string	splitArgsPRIVMSG(std::string args, std::string &message)
{
	size_t i;
	std::string destinataire;

	i = 0;
	while (args[i] && args[i] != ' ')
		i++;
	destinataire = args.substr(0, i);
	if (args[i] == ' ')
		i++;
	if (i == args.length() || (args[i] && args[i] != ':'))
		return ("");
	message = args.substr(i);
	return destinataire;
}

bool	isDigit(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
			return (false);
	}
	return (true);
}

