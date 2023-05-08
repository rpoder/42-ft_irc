# ft_irc
Bienvenue sur le IRC des petits poux !


Impossible de mettre close de fc dans le destructeur de user, car quand un user est cree puis copie dans la map users, la premiere version est detruite, or le fd doit tjr etre disponible depuis users

> solution :
close(fd) dans quit fonctionne si il est situé avant epoll_ctl(DEL)
+ close les fds ouverts de _users dans le desctructeur de Server
+ close le fd de epoll

kick ne s´affiche pas dans le bon canal 
> je trouve pas le probleme

part avec message d´erreur 
> ok