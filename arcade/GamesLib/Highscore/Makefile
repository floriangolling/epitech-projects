##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile shared library
##

NAME	=	arcade_highscore.so

SRC		=	Highscore.cpp	\
			SaveHighScore.cpp			\
			../../utils/Pixel/Pixel.cpp	\
			../../utils/Text/Text.cpp	\

OBJ		=	$(SRC:.cpp=.o)

CC		=	g++ -fPIC -std=c++17 -lstdc++fs
CFLAGS	=	-W -Wall -Wextra -Werror -I../../utils/ -I./
LDFLAGS	=	-shared

RM		=	rm -f

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CC) $(LDFLAGS) -o ../../lib/$(NAME) $(OBJ) -lstdc++fs
	@printf "[\033[0;36mbuilt\033[0m] %s\n" $(NAME)

%.o: %.cpp
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(RM) $(OBJ) $(RM_FILE)

fclean:
	@$(RM) $(OBJ) $(RM_FILE)
	@$(RM) ../../lib/$(NAME)
	@printf "[\033[0;31mdeleted\033[0m] %s\n" $(NAME)

re: fclean all

.PHONY: all clean fclean re