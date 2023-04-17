# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 21:14:29 by ronanpoder        #+#    #+#              #
#    Updated: 2023/04/17 17:03:21 by rpoder           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ircserv

CXX			=	c++

SRC			=	main.cpp \
				src/Server.cpp \
				src/User.cpp \
				src/Channel.cpp \
				src/ChannelMember.cpp \
				src/utils.cpp \
				src/replies.cpp \
				src/commands/JOIN_cmd.cpp \
				src/commands/NICK_cmd.cpp \
				src/commands/PASS_cmd.cpp \
				src/commands/USER_cmd.cpp \
				src/commands/PING_cmd.cpp \

OBJS_PATH	=	./obj/

OBJS		=	$(addprefix $(OBJS_PATH), $(SRC:.cpp=.o))

DEPS		=	$(OBJS:.o=.d)

CXXFLAGS	=	-MMD -Wall -Wextra -Werror -std=c++98 -I ./includes

EXEC		=	$(NAME)

all: $(NAME)

$(NAME):		$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(DEPS)
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(EXEC)

re:	fclean
	make all

$(OBJS_PATH)%.o : %.cpp
	mkdir -p $(dir $@)
	${CXX} ${CXXFLAGS} -c $< -o $@

-include $(DEPS)

.PHONY:	all clean fclean re
