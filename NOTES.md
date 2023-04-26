NICK - Margot
<!-- PAS OK IRSSI/NC -->
	431 ERR_NONICKNAMEGIVEN
		:rpoder!1@localhost 431 rpoder :No nickname given
<!-- irssi ok -->
<!-- nc ok -->
	ERR_NICKNAMEINUSE (433)
		:rpoder!1@localhost 433 rpoder rpoder :Nickname is already in use


USER - Margot
<!-- nc ok -->
<!-- irssi idk -->
	ERR_NEEDMOREPARAMS (461)
		:rpoder!1@localhost 461 rpoder USER :Not enough parameters
<!-- no verified -->
	ERR_ALREADYREGISTRED (462)
		:rpoder!1@localhost 462 rpoder :You may not reregister

PASS - Margot
<!-- nc not working, doesnt add * in response -->
	ERR_NEEDMOREPARAMS (461)
		: 461 *  :Not enough parameters

JOIN - Chloé
	(JOIN #test) -- > message normal quand aucune erreur
		:caubry!1@localhost 353 caubry = #test :@caubry
		:caubry!1@localhost 366 caubry #test :End of /NAMES list
		:caubry!1@localhost JOIN :#test

<!-- nc ok -->
	ERR_NEEDMOREPARAMS (461)
		:caubry!1@localhost 461 caubry JOIN :Not enough parameters

	ERR_BADCHANNELKEY (475)
		:caubry!1@localhost 475 caubry #test :Cannot join channel (+k)


MODE w/ options - Ronan
	+b ban - Margot
	+k set a key to a channel
	+o become channel operator

	ERR_NEEDMOREPARAMS (461) ok
		:caubry!1@localhost 461 caubry MODE :Not enough parameters

	ERR_NOSUCHCHANNEL (403) ok
		:caubry!1@localhost 403 caubry #key :No such channel

	ERR_NOTONCHANNEL (442) ok
		:caubry!1@localhost 442 caubry #test :You're not on that channel

	ERR_NOSUCHNICK (401) ok

	ERR_BANNEDFROMCHAN (474)

	ERR_CHANOPRIVSNEEDED (482) ok
		:caubry!1@localhost 482 caubry #test :You're not channel operator

	RPL_CHANNELMODEIS (324)
		:caubry!1@localhost 324 caubry #test +np
		:rpoder!1@localhost 324 rpoder #coucou +o rpoder
		:rpoder!1@localhost 324 rpoder #coucou +n

	ERR_KEYSET (467)
		:caubry!1@localhost 467 caubry #test :Channel key already set

	ERR_UNKNOWNMODE (472) ok
		:caubry!1@localhost 472 caubry z :is unknown mode char to me

KICK - Ronan ok
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

PART - Ronan ok
	PART
	PART #hey
	PART #hey, coucou

	(JOIN #test) -- > message normal quand aucune erreur
	(PART #test) -- > message normal quand aucune erreur
		:caubry!1@localhost PART #test

	ERR_NEEDMOREPARAMS (461) ok
		:caubry!1@localhost 461 caubry PART :Not enough parameters

	ERR_NOSUCHCHANNEL (403) ok
		:caubry!1@localhost 403 caubry #ok :No such channel

	ERR_NOTONCHANNEL (442)
		:mpou!1@localhost 442 mpou #test :You're not on that channel

QUIT - Ronan
	none

PING ok
	none

LIST
	RPL_LISTSTART (321), RPL_LIST (322), RPL_LISTEND (323)

PRIVMSG - Chloe

	QUand aucune erreur a envoyer a tous les fd membres sauf celui actuel :
		:mpou!1@localhost PRIVMSG #chan :test

	ERR_NEEDMOREPARAMS (461)
		:mpourrey!1@localhost 411 mpourrey :No recipient given ()
		:mpourrey!1@localhost 412 mpourrey :No text to send

	ERR_NOSUCHNICK (401)

	ERR_CANNOTSENDTOCHAN (404)
		:caubry!1@localhost 404 caubry #chan :Cannot send to channel
	ERR_TOOMANYTARGETS (407)


	RPL_AWAY (301)
		:mpourrey!1@localhost PRIVMSG rpoder : coucou toi
		(sur lui meme et le concerne)

NOTICE  - Chloe
	none

	:mpou!1@localhost NOTICE caubry :coucou
	:mpou!1@localhost NOTICE #chan :test

MARGOT
	passer channel._member en prive
	/quit doit envoyer un message dans tous les channels
	RPL de pass, user, nick

TODO
	ok prepSendToAll ony to active members
	ok MODE not enough params

