/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:22:04 by rpoder            #+#    #+#             */
/*   Updated: 2023/04/14 17:46:30 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main (int argc, char **argv)
{
	int port;

	if (argc != 3)
	{
		displayMessage("red", "Merci de mettre en arguments le numéro de port ainsi que le mot de passe.");
		displayMessage("red", "Exemple : ./ircserv 8080 mdp");
		return (0);
	}
	try
	{
		port = checkPortNumber(argv[1]);
		Server	server(port, argv[2]);
		
		server.start();
	}
	catch (std::exception &e)
	{
		displayMessage("red", e.what());
	}
	return (0);
}
