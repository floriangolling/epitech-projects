##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## lib
##

RM		=		rm -fr

NAME	=		libmy.a

OBJ		=		$(SRC:.c=.o)

SRC		=		my_getnbr.c					\
				my_putchar.c				\
				my_put_nbr.c				\
				my_putstr.c					\
				my_strcat.c					\
				my_strcmp.c					\
				my_strcpy.c					\
				my_strlen.c					\
				my_strncat.c				\
				my_strncpy.c				\
				my_strstr.c					\
				on_case.c					\
				my_strdup.c					\
				read_file.c					\
				my_nbrtoarray.c				\
				my_int_size.c

$(NAME):	$(OBJ)
			ar rc $(NAME) $(OBJ)
			cp my.h ./../../include/library
			cp libmy.a ../

all:		$(NAME)

clean:
			@$(RM) $(OBJ)
			@$(RM) *~
			@$(RM) *.o

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) ../libmy.a

re:			fclean all
