#include "Server.hpp"

bool    splitArgsPRIVMSG(std::string args, Channel *channel, ChannelMember *receveur, std::string &message)
{
    (void) args;
    (void) channel;
    (void) receveur;
    (void) message;
    // size_t space;
    // size_t i;

    // i = 0;
    // while (args[i] && args[i] != ' ')
    //     i++;
    // if (args[0] == '#')
    //     channel = findChannel(args.substr(0, i));
    // else
    //     receveur = findUser(args.substr(0, i));
    // if (args[i] == ' ')
    //     i++;
    // if (i == args.length() || (args[i] && args[i] != ':'))
    //     return false;
    // space = args.find(" ", i);
    // message = args.substr(i, space - i);
    return true;
}

std::string RPL_PRIVMSG(User *user, Channel &channel, std::string toSent)
{
	std::string message;

	message = prefix(user) + "PRIVMSG " + channel.getName() + " " + toSent + SUFFIX;
	return (message);
}

void    Server::PRIVMSG_cmd(int client_fd, User *user, std::string args)
{
    (void) client_fd;
    (void) user;
    (void) args;

    // std::string message;
    // Channel *chan;
    // ChannelMember *sender;
    // ChannelMember *receveur;

    displayMessage("orange", "[PRIVMSG_cmd function called]");

    // if (!splitArgsPRIVMSG(args, chan, receveur, message))
    //     prepSend(client_fd, buildErrorMessage(ERR_NEEDMOREPARAMS, user, "PRIVMSG", ":Not enough parameters"));
    // else
    // {
    //     if (args[0] == '#' && chan == NULL)
    //         prepSend(client_fd, buildErrorMessage(ERR_CANNOTSENDTOCHAN, user, "PRIVMSG", ":Cannot send to chan"));
    //     else if (args[0] == '#')
    //     {
    //         sender = chan->
    //     }
    //     else if (receveur == NULL)
    //     {

    //     }
    //     else
    //     {

    //     }
        // for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
        // {
        //     std::cout << *it << std::endl;
        //     chan = findChannel(*it);
        //     sender = chan->findMember(*user);
        //     chan->prepSendToAll(RPL_PRIVMSG(user, *chan, message), &Server::prepSend, sender);
        // }
        // for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
        // {
        //     std::cout << *it << std::endl;
        //     receveur = findChanne(*it);
        //     sender = chan->findMember(*user);
        //     chan->prepSend(RPL_PRIVMSG(user, *chan, message));
        // }

    // }
}