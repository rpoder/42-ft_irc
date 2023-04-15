<!-- EPOLL_CTL -->
<!-- masques events : le descipteur associe est disponible pour un appel de
read (EPOLLIN), ou write (EPOLLOUT).
Si le fd est initialise comme dispo pour un write, le client ecoute en continu,
et renvoie un event de type EPOLLOUT, qui trigger le epoll_wait -->
