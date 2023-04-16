<!-- EPOLL_CTL -->
<!-- masques events : le descipteur associe est disponible pour un appel de read (EPOLLIN) ou write (EPOLLOUT).
Si le fd est initialise comme dispo pour un write
le client ecoute en continu,
et renvoie un event de type EPOLLOUT
qui trigger le epoll_wait -->

TODO
cmds:

Margot
NICK
	431 ERR_NONICKNAMEGIVEN
		:rpoder!1@localhost 431 rpoder :No nickname given

	ERR_NICKNAMEINUSE (433)
		:rpoder!1@localhost 433 rpoder rpoder :Nickname is already in use

Margot
USER
	ERR_NEEDMOREPARAMS (461)
		:rpoder!1@localhost 461 rpoder USER :Not enough parameters

	ERR_ALREADYREGISTRED (462)
		:rpoder!1@localhost 462 rpoder :You may not reregister

PASS
	ERR_NEEDMOREPARAMS (461)
		: 461 *  :Not enough parameters

JOIN
	(JOIN #test) -- > message normal quand aucune erreur
		:caubry!1@localhost 353 caubry = #test :@caubry
		:caubry!1@localhost 366 caubry #test :End of /NAMES list
		:caubry!1@localhost JOIN :#test

	ERR_NEEDMOREPARAMS (461)
		:caubry!1@localhost 461 caubry JOIN :Not enough parameters

	RPL_TOPIC (332)

	ERR_BADCHANNELKEY (475)
		:caubry!1@localhost 475 caubry #test :Cannot join channel (+k)


MODE w/ options

	ERR_NEEDMOREPARAMS (461)
		:caubry!1@localhost 461 caubry MODE :Not enough parameters

	ERR_NOSUCHCHANNEL (403)
		:caubry!1@localhost 403 caubry #key :No such channel

	ERR_NOTONCHANNEL (442)
		:caubry!1@localhost 442 caubry #test :You're not on that channel

	ERR_NOSUCHNICK (401)

	ERR_CHANOPRIVSNEEDED (482)
		:caubry!1@localhost 482 caubry #test :You're not channel operator

	RPL_CHANNELMODEIS (324)
		:caubry!1@localhost 324 caubry #test +np

	ERR_KEYSET (467)
		:caubry!1@localhost 467 caubry #test :Channel key already set

	RPL_BANLIST (367)

	RPL_ENDOFBANLIST (368)

	ERR_UNKNOWNMODE (472)
		:caubry!1@localhost 472 caubry z :is unknown mode char to me

KICK
	:rpoder!1@localhost KICK #hey rpoder :t 251 rpoder :There are 1 users and 0 invisible on 1 servers
	# Do not ediPx�ight be symlinpx�v.conf. If you're

	ERR_NEEDMOREPARAMS (461)
		:rpoder!1@localhost 461 rpoder KICK :Not enough parameters

	ERR_NOSUCHCHANNEL (403)
		:rpoder!1@localhost 403 rpoder #hey :No such channel

	ERR_NOTONCHANNEL (442)
		:rpoder!1@localhost 441 rpoder jdshfjk #hey :They aren't on that channel

	ERR_CHANOPRIVSNEEDED (482)
		:rpoder!1@localhost 482 rpoder #coucou :You're not channel operator

PART
	(JOIN #test) -- > message normal quand aucune erreur
		:caubry!1@localhost PART #test

	ERR_NEEDMOREPARAMS (461)
		:caubry!1@localhost 461 caubry PART :Not enough parameters

	ERR_NOSUCHCHANNEL (403)
		:caubry!1@localhost 403 caubry #ok :No such channel

	ERR_NOTONCHANNEL (442)
		:mpou!1@localhost 442 mpou #test :You're not on that channel

QUIT
	none
PING
	none
INVITE

	ERR_NEEDMOREPARAMS (461)
		:rpoder!1@localhost 461 rpoder INVITE :Not enough parameters

	ERR_NOSUCHNICK (401)
		:rpoder!1@localhost 401 rpoder blabla :No such nick/channel

	ERR_NOTONCHANNEL (442)
		:rpoder!1@localhost 442 rpoder #coucou3 :You're not on that channel

	ERR_USERONCHANNEL (443)
		not handled

	ERR_CHANOPRIVSNEEDED (482)
		not handled

	RPL_INVITING(341)
		:rpoder!1@localhost INVITE mpourrey #hey
		(sur lui meme et le concerne)
<!-- LIST
	RPL_LISTSTART (321), RPL_LIST (322), RPL_LISTEND (323) -->
<!-- NAMES
	RPL_NAMREPLY (353), RPL_ENDOFNAMES (366) -->
PRIVMSG
	ERR_NEEDMOREPARAMS (461)
		:mpourrey!1@localhost 411 mpourrey :No recipient given ()
		:mpourrey!1@localhost 412 mpourrey :No text to send

	ERR_NOSUCHNICK (401)

	ERR_CANNOTSENDTOCHAN (404)

	ERR_TOOMANYTARGETS (407)


	RPL_AWAY (301)
		:mpourrey!1@localhost PRIVMSG rpoder : coucou toi
		(sur lui meme et le concerne)

<!-- TOPIC
	ERR_NEEDMOREPARAMS (461), ERR_NOTONCHANNEL (442), ERR_CHANOPRIVSNEEDED (482), RPL_TOPIC (332), RPL_NOTOPIC (331) -->
NOTICE
	none









CAP LS
PASS mdp
NICK rpoder
USER 1 2 3 :4


CAP LS
PASS mdp
NICK mpourrey
USER 1 2 3 :4
