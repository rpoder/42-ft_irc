/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   Server.cpp										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rpoder <rpoder@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/09 19:11:40 by rpoder			#+#	#+#			 */
/*   Updated: 2023/04/09 19:43:20 by rpoder		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "Server.hpp"

//!-------------------------------CONSTRUCTOR-----------------------------------

Server::Server()
{

}

Server::Server(const Server &copy)
{
	*this = copy;
}

//!-------------------------------DESTRUCTOR------------------------------------

Server::~Server()
{
	int yes;

	yes = 1;
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		//TODO throw exception instead
		perror("setsockopt");
		exit(1);
	}
	freeaddrinfo(_serv_info);
}

//!-------------------------------OPERATOR--------------------------------------

Server	&Server::operator=(const Server &copy)
{
	//TODO complete this part
	(void) copy;
	return(*this);
}

//!-------------------------------ACCESSORS-------------------------------------

//!-------------------------------FUNCTIONS-------------------------------------

void	Server::listen(unsigned int port)
{
	(void) port;
	struct sockaddr_storage	their_addr;
	int						new_fd;
	socklen_t				addr_size;

	//TODO check if port is in range (defines are in the header)
	//TODO check if memset is forbidden
	memset(&_hints, 0, sizeof _hints); // make sure the struct is empty
	_hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
	_hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	_hints.ai_flags = AI_PASSIVE; // fill in my IP for me

	_status = getaddrinfo("localhost", "3490", &_hints, &_serv_info);
	if (_status != 0)
		throw (Server::ServerInitException());
	_socket_fd = socket(_serv_info->ai_family, _serv_info->ai_socktype, _serv_info->ai_protocol);
	if (_socket_fd == -1)
		throw (Server::ServerInitException());
		//? ERRNO is available for this ret
		//? maybe check return errno in a arg_exception
	if (bind(_socket_fd, _serv_info->ai_addr, _serv_info->ai_addrlen) != 0)
		throw (Server::ServerInitException());
	if (::listen(_socket_fd, CONNECTIONS_MAX))
		throw (Server::ServerInitException());

	addr_size = sizeof(their_addr);
	new_fd = accept(_socket_fd, (struct sockaddr *)&their_addr, &addr_size);
}

//!-----------------------------MEMBER CLASSES----------------------------------

const char	*Server::ServerInitException::what() const throw()
{

	return ("could't instantiate the server");
}
