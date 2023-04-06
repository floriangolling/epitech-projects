##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile shared library
##

NAME		=	arcade

SRC			=		src/Core.cpp	\
					src/Main.cpp	\
					../utils/LibLoader.cpp	\

OBJS		=	$(SRC:.cpp=.o)

CC		=	g++ -fPIC -std=c++17 -lstdc++fs
CFLAGS		+=	-W -Wall -Wextra -Werror -I../utils/ -I./src/
LDFLAGS		+=	-ldl

RM			=	rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
			@$(CC) -o ../$(NAME) $(OBJS) $(LDFLAGS) -lstdc++fs
			@printf "[\033[0;36mbuilt\033[0m] %s\n" $(NAME)

%.o: %.cpp
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)
	@printf "[\033[0;31mdeleted\033[0m] %s\n" $(NAME)

re:	fclean all

.PHONY: all clean fclean re