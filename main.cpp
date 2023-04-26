/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:22:04 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/25 18:26:58 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <csignal>

bool stop = false;

void signalHandler( int signum ) {
	std::cout << "Interrupt signal (" << signum << ") received.\n";
	exit(signum);
}

int main (int argc, char **argv)
{
	int port;

	if (argc != 3)
	{
		displayMessage("red", "ERR:	Please insert port and password.");
		displayMessage("orange", "	e.g: ./ircserv 8080 password");
		return (1);
	}
	signal(SIGINT, signalHandler);
	try
	{
		port = checkPortNumber(argv[1]);
		Server	server(port, argv[2]);
		server.start();
	}
	catch (std::exception &e)
	{
		displayMessage("red", "ERR:	", false);
		displayMessage("red", e.what());
	}
	return (0);
}
