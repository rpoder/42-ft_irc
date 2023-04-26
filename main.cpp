/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:22:04 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/26 12:22:01 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <csignal>

bool is_running = true;

void signalHandler( int signum ) {
	std::cout << "Interrupt signal (" << signum << ") received.\n";
	is_running = false;
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
		while (is_running == true)
			server.waitEvents();
	}
	catch (std::exception &e)
	{
		displayMessage("red", "ERR:	", false);
		displayMessage("red", e.what());
	}
	return (0);
}
